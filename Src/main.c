#include "main.h"
#include"stm32f1xx.h"
#include"init.h"
#include"rcc.h"
#include"gpio.h"
int main(void){

    rcc_init();
    init();
    gpio_init();
  while (1)
  {
      Delay_ms(200);
GPIOC->BSRR|=GPIO_BSRR_BR13;
Delay_ms(200);
GPIOC->BSRR|=GPIO_BSRR_BS13;
  }
}




uint16_t DoFullPID(uint16_t In, uint16_t Ref, uint16_t *Coeff)
{
  uint16_t Kp, Ki, Kd, Output, Error;
  static uint16_t IntTerm_C, PrevError_C;
  Error = Ref - In;
  Kp = Coeff[0];
  Ki = Coeff[1];
  Kd = Coeff[2];

  IntTerm_C += Ki*Error;
  Output = Kp * Error;
  Output += IntTerm_C;
  Output += Kd * (Error - PrevError_C);

  PrevError_C = Error;

  return (Output);
}











void Error_Handler(void)
{

}

