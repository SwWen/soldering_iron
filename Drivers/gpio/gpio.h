#ifndef GPIO_H
#define GPIO_H
#include"stm32f1xx.h"

#define PC13_on  (GPIOC->BSRR=GPIO_BSRR_BS13)
#define PC13_off (GPIOC->BSRR=GPIO_BSRR_BR13)
#define DIG1_ON   (GPIOB->BSRR|=GPIO_BSRR_BS0)
#define DIG1_OFF   (GPIOB->BSRR|=GPIO_BSRR_BR0)
#define DIG2_ON   (GPIOB->BSRR|=GPIO_BSRR_BS4)
#define DIG2_OFF   (GPIOB->BSRR|=GPIO_BSRR_BR4)
#define DIG3_ON   (GPIOB->BSRR|=GPIO_BSRR_BS12)
#define DIG3_OFF   (GPIOB->BSRR|=GPIO_BSRR_BR12)
#define DIG4_ON   (GPIOB->BSRR|=GPIO_BSRR_BS6)
#define DIG4_OFF   (GPIOB->BSRR|=GPIO_BSRR_BR6)


void gpio_init(void);

#endif // GPIO_H
