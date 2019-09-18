#include"init.h"
void __attribute__ ((weak)) _init(void)  {}

static __IO uint32_t __ms;

void init(void){
//FLASH->KEYR = 0x45670123;
//FLASH->KEYR = 0xCDEF89AB;
SystemCoreClockUpdate();
while( SysTick_Config(SystemCoreClock/1000));
}


void Delay_ms(uint32_t nTime)
{
  uint32_t start = __ms;
  while((__ms-start) < nTime);
}

uint32_t TimingDelay_Increment(void)
{

  __ms ++;
  return __ms;
}

//Обработчик прерывания системного таймера
void SysTick_Handler(void)
{
  TimingDelay_Increment();
}
