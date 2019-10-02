#include"disp.h"
#include"stm32f1xx.h"
#include"gpio.h"

uint16_t dig[12]={0x280,0xE8A,0x30C,0xA0C,0xE06,\
                  0xA24,0x224,0xE8C,0x204,0xA04,0xFAA,0x704};
__IO uint16_t d_dig=0;
__IO uint8_t d_symb=0;
/*  11 e
 *  10 d
 *  9 c
 *
 *
 *
 */
void disp_init(void){
    RCC->APB1ENR|=RCC_APB1ENR_TIM4EN;
    TIM4->PSC=8;
    TIM4->ARR = 1000;
    TIM4->CCR1 = 500;
    TIM4->DIER|=TIM_DIER_UIE|TIM_DIER_CC1IE;
    TIM4->CR1 |=TIM_CR1_DIR;
    TIM4->CR1 |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM4_IRQn);
}
uint8_t dot;
void TIM4_IRQHandler(void){
    static __IO uint8_t cnt;
    if(TIM4->SR&TIM_SR_CC1IF){
        cnt++;
        if(cnt==1){
            GPIOB->BSRR|=dig[d_symb];
            if(dot&1<<0){
                 GPIOB->BSRR|=1<<(9+16);
            }
            DIG1_ON;}
        if(cnt==2){
            GPIOB->BSRR|=dig[d_dig % 1000 / 100];
            if(dot&1<<1){
                GPIOB->BSRR|=1<<(9+16);
            }
            DIG2_ON;}
        if(cnt==3){
            GPIOB->BSRR|=dig[d_dig % 100/10];
            if(dot&1<<2){
                GPIOB->BSRR|=1<<(9+16);
            }
            DIG3_ON;}
        if(cnt==4){
            GPIOB->BSRR|=dig[d_dig % 10];
            if(dot&1<<3){
                GPIOB->BSRR|=1<<(9+16);
            }
            DIG4_ON;}
        if(cnt>4){
            cnt=0;}

        TIM4->SR&=~TIM_SR_CC1IF;
    }
    if(TIM4->SR&TIM_SR_UIF){
        GPIOB->BSRR|=0xFFFF<<16;
        TIM4->SR&=~TIM_SR_UIF;
    }

}

