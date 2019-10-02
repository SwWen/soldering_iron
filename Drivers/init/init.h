#ifndef INIT_H
#define INIT_H
#include"stm32f1xx.h"

void Delay_ms(uint32_t nTime);
void init(void);
extern __IO uint32_t __ms;
extern __IO uint32_t __pid;
#endif // INIT_H
