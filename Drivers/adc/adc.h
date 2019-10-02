#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED
#include"stm32f1xx.h"
void adc_init(void);
void dma_init(void);
uint16_t adc_value(void);

#define COUNT_FILTER    256

typedef union
{
    unsigned int Val;
    struct
    {
        unsigned Flag:1;        //Флаг заполнения суммы
        unsigned Index:8;       //Хранение индекса буфера
        unsigned Filter_sum:23; //Регистр суммы для усреднения
    } Reg;
} FILTER_REG;

uint16_t  filter_sred(uint16_t ADC_val,uint16_t* buf, FILTER_REG* filter_reg);


#endif // ADC_H_INCLUDED
