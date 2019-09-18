#ifndef GPIO_H
#define GPIO_H
#include"stm32f1xx.h"

#define PC13_on  (GPIOC->BSRR=GPIO_BSRR_BS13)
#define PC13_off (GPIOC->BSRR=GPIO_BSRR_BR13)


void gpio_init(void);

#endif // GPIO_H
