
#include "main.h"
#include"stm32f1xx.h"
int main(void)


{

RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;
GPIOC->CRH|=GPIO_CRH_MODE13_0;
  while (1)
  {
GPIOC->BSRR|=GPIO_BSRR_BR13;
GPIOC->BSRR|=GPIO_BSRR_BS13;
  }
}















void Error_Handler(void)
{

}

