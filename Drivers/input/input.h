#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
#include"stm32f1xx.h"
#define NULL 0
enum{
SHORT_CLK =10,
LONG_CLK =15,
DUBBLE_CLK =20

};
typedef void (*callbackFunction)(void);
void OBInit (void);
extern __IO uint32_t timestamp;
extern uint8_t BtnFlags;





// ----- Функции машины состояний -----
// Функция tick должна вызываться периодически, с интервалом времени
// порядка 10 мс - чтобы библиотека могла обработать события кнопки.
void OBtick(void);
#endif // ONE_BUTTON_H_INCLUDED
