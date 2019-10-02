#ifndef DISP_H
#define DISP_H

#include"stm32f1xx.h"
extern __IO uint16_t d_dig;
extern __IO uint8_t d_symb;
extern   uint8_t dot;
extern uint16_t dig[12];
void disp_init(void);

#define EMPTY 10
#define P 11









#endif // DISP_H
