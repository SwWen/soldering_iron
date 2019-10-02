#include"adc.h"
#include"stm32f1xx.h"
static uint16_t buf_ADC[256];
static FILTER_REG FLT;
void adc_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL &= ~GPIO_CRL_CNF6;
    GPIOC->CRL &= ~GPIO_CRL_MODE6;
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN ;
    ADC1->CR2 |= ADC_CR2_CAL;
    while (!(ADC1->CR2 & ADC_CR2_CAL))
        ADC1->SMPR2 = ADC_SMPR2_SMP0;
    ADC1->CR2 = ADC_CR2_EXTSEL | ADC_CR2_ADON | ADC_CR2_EXTTRIG;//|ADC_CR2_CONT;
    ADC1->CR2  |=    ADC_CR2_DMA;
    ADC1->CR2 &= ~ ADC_CR2_CONT;
    ADC1->SQR1 = 0x00000000;
    ADC1->SQR3 = 0x00000000;
    ADC1->CR2 |= ADC_CR2_SWSTART;

}

#define DMA_BUFF_SIZE 1
static  uint16_t buff[DMA_BUFF_SIZE];
void dma_init(void){



    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    DMA1_Channel1->CPAR = (uint32_t) &ADC1->DR;
    DMA1_Channel1->CMAR = (uint32_t)buff;
    DMA1_Channel1->CCR &= ~DMA_CCR_DIR;
    DMA1_Channel1->CNDTR = DMA_BUFF_SIZE;
    DMA1_Channel1->CCR &= ~DMA_CCR_PINC;
    DMA1_Channel1->CCR |= DMA_CCR_MINC;
    DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0;
    DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0;
    DMA1_Channel1->CCR |= DMA_CCR_PL;
    DMA1_Channel1->CCR |= DMA_CCR_CIRC;
    DMA1_Channel1->CCR |= DMA_CCR_EN;

}





uint16_t adc_value(void){
    uint16_t adc_value;
    ADC1->CR2 |= ADC_CR2_SWSTART;
    //adc_value*100/4096;
    adc_value =(buff[0]);
    return filter_sred(adc_value,buf_ADC,&FLT);

}


uint16_t  filter_sred(uint16_t ADC_val,uint16_t* buf, FILTER_REG* filter_reg){
    if (filter_reg->Reg.Flag){
        filter_reg->Reg.Filter_sum-=buf[filter_reg->Reg.Index];
        filter_reg->Reg.Filter_sum+=ADC_val;
        buf[filter_reg->Reg.Index]=ADC_val;
        if (filter_reg->Reg.Index>=COUNT_FILTER-1){
            filter_reg->Reg.Index=0;
        }
        else{
            filter_reg->Reg.Index++;
        }
    }
    else{
        filter_reg->Reg.Filter_sum+=ADC_val;
        buf[filter_reg->Reg.Index]=ADC_val;
        if (filter_reg->Reg.Index>=COUNT_FILTER-1){
            filter_reg->Reg.Index=0;
            filter_reg->Reg.Flag=1;
        }
        else{
            filter_reg->Reg.Index++;
        }
    }
    return (filter_reg->Reg.Filter_sum/COUNT_FILTER);
}







