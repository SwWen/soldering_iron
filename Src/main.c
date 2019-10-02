#include "main.h"
#include"stm32f1xx.h"
#include"init.h"
#include"rcc.h"
#include"gpio.h"
#include"disp.h"
#include"input.h"
#include"adc.h"
#include"solder.h"

int main(void){
    rcc_init();
    init();
    gpio_init();
    disp_init();
    adc_init();
    dma_init();
    up.port=GPIOA;
    up.pin=GPIO_IDR_IDR3;
    dwn.port=GPIOA;
    dwn.pin=GPIO_IDR_IDR4;
    up_dwn.port=GPIOA;
    up_dwn.pin=GPIO_IDR_IDR3|GPIO_IDR_IDR4;
    OBInit(&up);
    OBInit(&dwn);
    OBInit(&up_dwn);
    d_symb=EMPTY;
 solder_init();
  while (1)
  {

  // d_dig=adc_value();
main_screen();
}

//d_dig=dwn.btn_flag;
  }













void Error_Handler(void)
{

}

