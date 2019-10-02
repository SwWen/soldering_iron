
#include "input.h"
#include"init.h"
#define CLICKTICK 200   // Количество тиков, которое должно пройти, чтобы
                   // было засчитано короткое нажатие на кнопку.
#define PRESS_TICKS 1000   // Количество тиков, которое должно пройти, чтобы
                   // было засчитано длинное нажатие на кнопку.
#define DEBOUNCE_TICKS  50 // количество тиков для подавления дребезга.


// Переменные ниже хранят информацию машины состояний, сохраняющуюся
// между отдельными вызовами tick(). Они инициализируются один раз
// при старте программы, и обновляются каждый раз при вызове функции
// tick().


__IO uint32_t timestamp;

btn up;
btn dwn;
btn up_dwn;
void OBInit (btn *button)
{

  button->state = 0; // Начальное состояние state 0: в нем ожидается первое нажатие
              // на кнопку.
  button->isLongPressed = RESET;  // Флаг, отслеживающий долгое нажатие.
  button->btn_flag=0;
}

void OBtick(btn *button)
{

    static unsigned long _startTime; // Эта переменная будет установлена в state 1.
  // Детектирование входных данных
  uint8_t buttonLevel = (button->port->IDR & button->pin)?SET:RESET; // текущий входной сигнал кнопки.
  uint32_t now = timestamp; // текущее (относительное) время в миллисекундах.
  // Реализация машины состояний
  if (button->state == 0)
  { // Ожидание нажатия на кнопку.
    if (buttonLevel == RESET)
    {
      button->state = 1;       // переход в состояние state 1
      _startTime = now; // запоминание точки отсчета времени
    }
  }
  else if (button->state == 1)
  { // Ожидание отпускания кнопки.
    if ((buttonLevel == SET) && (now < _startTime + DEBOUNCE_TICKS))
    {
      // Кнопка была отпущена достаточно быстро, чтобы можно было
      // считать это дребезгом контактов. Поэтому происходит
      // переход в начальное состояние, без каких-либо вызовов функций.
      button->state = 0;
    }
    else if (buttonLevel == SET)
    {
      button->state = 2; // переход в состояние state 2
    }
    else if ((buttonLevel == RESET) && (now > _startTime + PRESS_TICKS))
    {
      button->isLongPressed = SET;  // зарегистрировать долгое нажатие
          button->btn_flag=15;
      button->state = 6; // переход в состояние state 6
    }
    else
    {
      // Ожидание, пока остаемся в этом состоянии.
    }
  }
  else if (button->state == 2)
  {
    // Ожидание вторичного нажатия на кнопку или истечения таймаута.
    if (now > _startTime + CLICKTICK)
    {
      // Это было простое короткое нажатие
  button->btn_flag=10;
      button->state = 0; // возврат в исходное состояние.
    }
    else if (buttonLevel == RESET)
    {
      button->state = 3; // переход в состояние state 3
    }
  }
  else if (button->state == 3)
  { // Ожидание завершающего опускания кнопки.
    if (buttonLevel == SET)
    {
      // this was a 2 click sequence.
          button->btn_flag=20;
      button->state= 0; // возврат в исходное состояние.
    }
  }
  else if (button->state == 6)
  { // Ожидание опускания кнопки после долгого нажатия.
    if (buttonLevel == SET)
    {
      button->isLongPressed = RESET; // Отслеживание состояния долгого нажатия.
      button->state = 0; // возврат в исходное состояние.
    }
    else
    {
      // Кнопка была нажата длительное время.
      button->isLongPressed = SET;  // Отслеживание состояния долгого нажатия.

    }
  }
}

