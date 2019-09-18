
#include "input.h"

#define CLICKTICK 300   // Количество тиков, которое должно пройти, чтобы
                   // было засчитано короткое нажатие на кнопку.
#define PRESS_TICKS 1000   // Количество тиков, которое должно пройти, чтобы
                   // было засчитано длинное нажатие на кнопку.
#define DEBOUNCE_TICKS  20 // количество тиков для подавления дребезга.
static uint8_t _isLongPressed;

// Переменные ниже хранят информацию машины состояний, сохраняющуюся
// между отдельными вызовами tick(). Они инициализируются один раз
// при старте программы, и обновляются каждый раз при вызове функции
// tick().
 static uint8_t _state;
static unsigned long _startTime; // Эта переменная будет установлена в state 1.
uint8_t BtnFlags;
__IO uint32_t timestamp;
void OBInit (void)
{

  _state = 0; // Начальное состояние state 0: в нем ожидается первое нажатие
              // на кнопку.
  _isLongPressed = RESET;  // Флаг, отслеживающий долгое нажатие.
BtnFlags=0;
}


void OBtick(void)
{
  // Детектирование входных данных
  uint8_t buttonLevel = (GPIOB->IDR & GPIO_IDR_IDR3)?SET:RESET; // текущий входной сигнал кнопки.
  uint32_t now = timestamp; // текущее (относительное) время в миллисекундах.
  // Реализация машины состояний
  if (_state == 0)
  { // Ожидание нажатия на кнопку.
    if (buttonLevel == RESET)
    {
      _state = 1;       // переход в состояние state 1
      _startTime = now; // запоминание точки отсчета времени
    }
  }
  else if (_state == 1)
  { // Ожидание отпускания кнопки.
    if ((buttonLevel == SET) && (now < _startTime + DEBOUNCE_TICKS))
    {
      // Кнопка была отпущена достаточно быстро, чтобы можно было
      // считать это дребезгом контактов. Поэтому происходит
      // переход в начальное состояние, без каких-либо вызовов функций.
      _state = 0;
    }
    else if (buttonLevel == SET)
    {
      _state = 2; // переход в состояние state 2
    }
    else if ((buttonLevel == RESET) && (now > _startTime + PRESS_TICKS))
    {
      _isLongPressed = SET;  // зарегистрировать долгое нажатие
          BtnFlags=15;
      _state = 6; // переход в состояние state 6
    }
    else
    {
      // Ожидание, пока остаемся в этом состоянии.
    }
  }
  else if (_state == 2)
  {
    // Ожидание вторичного нажатия на кнопку или истечения таймаута.
    if (now > _startTime + CLICKTICK)
    {
      // Это было простое короткое нажатие
  BtnFlags=10;
      _state = 0; // возврат в исходное состояние.
    }
    else if (buttonLevel == RESET)
    {
      _state = 3; // переход в состояние state 3
    }
  }
  else if (_state == 3)
  { // Ожидание завершающего опускания кнопки.
    if (buttonLevel == SET)
    {
      // this was a 2 click sequence.
          BtnFlags=20;
      _state = 0; // возврат в исходное состояние.
    }
  }
  else if (_state == 6)
  { // Ожидание опускания кнопки после долгого нажатия.
    if (buttonLevel == SET)
    {
      _isLongPressed = RESET; // Отслеживание состояния долгого нажатия.
      _state = 0; // возврат в исходное состояние.
    }
    else
    {
      // Кнопка была нажата длительное время.
      _isLongPressed = SET;  // Отслеживание состояния долгого нажатия.

    }
  }
}

