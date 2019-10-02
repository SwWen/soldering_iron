#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
#include"stm32f1xx.h"
#define NULL 0
enum{
SHORT_CLK =10,
LONG_CLK =15,
DUBBLE_CLK =20

};

typedef struct {
    GPIO_TypeDef *port;
    uint32_t pin;
    uint32_t btn_flag;
    uint8_t state;
     uint8_t isLongPressed;
} btn;
extern __IO uint32_t timestamp;
extern uint8_t BtnFlags;
void OBtick(btn *button);
void OBInit (btn *button);
extern btn up_dwn;
extern btn up;
extern btn dwn;
// ----- Функции машины состояний -----
// Функция tick должна вызываться периодически, с интервалом времени
// порядка 10 мс - чтобы библиотека могла обработать события кнопки.
#endif // ONE_BUTTON_H_INCLUDED
