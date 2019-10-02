#include"solder.h"
#include"stm32f1xx.h"
#include"input.h"
#include"disp.h"
#include"flash.h"
#include"init.h"
#include"adc.h"
#include"math.h"
#define flash_write() (Internal_Flash_Write((uint8_t*)&ee_set,FLASH_PAGE_63,sizeof(ee_set)))
void blink(uint8_t dot_mask, uint16_t count);
void pwm_init(void);
static uint16_t Coeff[3];
uint16_t DoFullPID(uint16_t In, uint16_t Ref, uint16_t *Coeff);
uint8_t button_handler(void);
void work(void);
void settings(void);
static uint8_t menu_i=1;
static uint16_t set;
static eep_t ee_set;
void solder_init(void){
    ee_set=flash_read(FLASH_PAGE_63);
set=ee_set.param[9];
pwm_init();
Coeff[0]=40;
Coeff[1]=3;
Coeff[2]=0;
}
void main_screen(void){

    switch (menu_i) {
    case 1:{

        work();
        break;
    }
    case 2:{
settings();
break;
    }
    }

          OBtick(&up_dwn);
          OBtick(&up);
          OBtick(&dwn);


}

uint8_t button_handler(void){
      uint8_t i=0;
    if(up.btn_flag==SHORT_CLK){
     i=1;
     up.btn_flag=0;
    }

    if(up.btn_flag==LONG_CLK){
     i=10;
      up.btn_flag=0;
     up.state=0;
    }
    if(dwn.btn_flag==SHORT_CLK){
     i=2;
     dwn.btn_flag=0;
    }
    if(up_dwn.btn_flag==SHORT_CLK){
     i=3;
     up_dwn.btn_flag=0;
    }
    if(dwn.btn_flag==LONG_CLK){
     i=20;
      dwn.btn_flag=0;
     dwn.state=0;

    }

    if(up.btn_flag==DUBBLE_CLK){
     i=11;
      up.btn_flag=0;
     up.state=0;

    }
    if(dwn.btn_flag==DUBBLE_CLK){
     i=22;
      dwn.btn_flag=0;
     dwn.state=0;

    }

    if(up_dwn.btn_flag==LONG_CLK){
     i=30;
      up_dwn.btn_flag=0;
     up_dwn.state=0;

    }
    return i;
}

void blink(uint8_t dot_mask, uint16_t count){
    static  uint32_t cnt;
    if(__ms%100==0){
        cnt++;}
    if(cnt<(count/2)){
        dot|=dot_mask;
    }else dot=0;
    if(cnt>count){
        cnt=0;
    }
}


void work(void){
    uint16_t cur;
    static int8_t i;
cur=(adc_value()-1760)/3;

  if(__pid>20){
  TIM3->CCR1=DoFullPID(cur,set,Coeff);
  d_dig=set;
 __pid=0;}
    d_symb=EMPTY;
    switch (button_handler()) {

    case 1:{
     if(up.isLongPressed){set--;up.isLongPressed=0;}
     set++;

     break;
    }
    case 2:{
        if(dwn.isLongPressed){set++;dwn.isLongPressed=0;}
        set--;
        break;
    }
    case 10:{
set+=10;
        break;

    }
    case 20:{
set-=10;
 break;
    }
    case 11:{
        i++;
        if(i>3)i=0;
        set=ee_set.param[i];
        break;
    }
    case 22:{
        i--;
        if(i<0)i=3;
        set=ee_set.param[i];
                break;

    }
    case 30:{

        menu_i=2;
        d_symb=1;
      //  flash_write();
        ee_set=flash_read(FLASH_PAGE_63);
        break;

    }
    case 3:{
        ee_set.param[9]=set;
     flash_write();
      break;
    }
    }
ee_set.set[0]=i;
if((cur<set-2)||(cur>set+2)){
    blink(1,500);
}else{
    dot=8;
}


}

void settings(void){
    static uint8_t param;
    static uint16_t value;
    switch (button_handler()) {

    case 1:{
     if(up.isLongPressed){value--;up.isLongPressed=0;}
     value=ee_set.param[param];
     value++;
     ee_set.param[param]=value;
     break;
    }
    case 2:{
        if(dwn.isLongPressed){value++;dwn.isLongPressed=0;}
        value=ee_set.param[param];
        value--;
        ee_set.param[param]=value;
        break;
    }
    case 10:{
        value=ee_set.param[param];
        value+=10;
        ee_set.param[param]=value;
        break;

    }
    case 20:{
        value=ee_set.param[param];
        value-=10;
        ee_set.param[param]=value;
        break;
    }
    case 11:{
        param++;
        break;
    }
    case 22:{
        param--;
        break;
    }
    case 30:{
        d_symb=EMPTY;
        menu_i=1;
flash_write();
ee_set=flash_read(FLASH_PAGE_63);
        break;

    }

    default:{break;}

    }


d_symb=param;
dot=1;
d_dig=ee_set.param[param];
}


uint16_t DoFullPID(uint16_t In, uint16_t Ref, uint16_t *Coeff)
{
  uint16_t Kp, Ki, Kd;
  int16_t   Output, Error;
static int16_t PrevError_C = 0, IntTerm_C = 0;
  Error = Ref - In;
  Kp = Coeff[0];
  Ki = Coeff[1];
  Kd = Coeff[2];

  IntTerm_C += Ki*Error;
  if(IntTerm_C<0){IntTerm_C=0;}
  if(IntTerm_C>400){IntTerm_C=400;}
  Output = Kp * Error;
  Output += IntTerm_C;
  Output += Kd * (Error - PrevError_C);

  PrevError_C = Error;
if(Output<0){Output=0;}
if(Output>1000){Output=1000;}
  return (Output);
}


void pwm_init(void){
    GPIOA->CRL |= GPIO_CRL_MODE6;
    GPIOA->CRL &= ~GPIO_CRL_CNF6;
    GPIOA->CRL |= GPIO_CRL_CNF6_1;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->PSC=8;
    TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM3->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);
    TIM3->ARR = 1000;
    TIM3->CCR1 = 0;
    TIM3->CCER |= TIM_CCER_CC1E;
    TIM3->CR1 |= TIM_CR1_CEN;
}
