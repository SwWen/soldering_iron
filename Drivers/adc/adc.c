#include"adc.h"
#include"stm32f1xx.h"
static uint16_t buf_ADC[256];
static FILTER_REG FLT;
void adc_init(void)
{

    //разрешаем тактирование порта А
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        //настраиваем вывод для работы АЦП в режим аналогового входа
    GPIOA->CRL &= ~GPIO_CRL_CNF6;
    GPIOC->CRL &= ~GPIO_CRL_MODE6;
    //так как тактовая частота АЦП не должна превышать 14MHz
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8;
    //разрешаем тактирование АЦП
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN ;
        //запускаем калибровку и ждем пока завершится,  в симуляторе это не работает, в железе делать обязательно
       ADC1->CR2 |= ADC_CR2_CAL;
         while (!(ADC1->CR2 & ADC_CR2_CAL))
    //разрешаем прерывание от АЦП
 //   NVIC->ISER[0] |= NVIC_ISER_SETENA_18;
    //для первого канала между выборками 7.5 цикла
    ADC1->SMPR2 = ADC_SMPR2_SMP1_0;
    //разрешаем прерывания по окончанию преобразования
  //  ADC1->CR1 = ADC_CR1_EOCIE;
    //разрешаем запуск от SWSTAR, разрешаем работу АЦП, разрешаем запуск внешним сигналам, непрерывное преобразования
    ADC1->CR2 = ADC_CR2_EXTSEL | ADC_CR2_ADON | ADC_CR2_EXTTRIG;//|ADC_CR2_CONT;
    ADC1->CR2  |=    ADC_CR2_DMA;
    ADC1->CR2 &= ~ ADC_CR2_CONT;
    //длина последовательности равна 1, первый канал
//    ADC1->SQR1 = 0x00000000;
//    ADC1->SQR2 = 0x00000000;
    ADC1->SQR3 |= (ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_2);
    //запускаем АЦП
 ADC1->CR2 |= ADC_CR2_SWSTART;

}

#define DMA_BUFF_SIZE 1//Размер буфера
static  uint16_t buff[DMA_BUFF_SIZE];//Буфер
void dma_init(void){



    RCC->AHBENR |= RCC_AHBENR_DMA1EN; //Разрешаем тактирование первого DMA модуля
    DMA1_Channel1->CPAR = (uint32_t) &ADC1->DR; //Указываем адрес периферии - регистр результата преобразования АЦП для регулярных каналов
    DMA1_Channel1->CMAR = (uint32_t)buff; //Задаем адрес памяти - базовый адрес массива в RAM
    DMA1_Channel1->CCR &= ~DMA_CCR_DIR; //Указываем направление передачи данных, из периферии в память
    DMA1_Channel1->CNDTR = DMA_BUFF_SIZE; //Количество пересылаемых значений
    DMA1_Channel1->CCR &= ~DMA_CCR_PINC; //Адрес периферии не инкрементируем после каждой пересылки
    DMA1_Channel1->CCR |= DMA_CCR_MINC; //Адрес памяти инкрементируем после каждой пересылки.
    DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0; //Размерность данных периферии - 16 бит
    DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0; //Размерность данных памяти - 16 бит
    DMA1_Channel1->CCR |= DMA_CCR_PL; //Приоритет - очень высокий
    DMA1_Channel1->CCR |= DMA_CCR_CIRC; //Разрешаем работу DMA в циклическом режиме
    DMA1_Channel1->CCR |= DMA_CCR_EN; //Разрешаем работу 1-го канала DMA


}





uint16_t adc_value(void){
uint16_t adc_value;
ADC1->CR2 |= ADC_CR2_SWSTART;
//adc_value*100/4096;
 adc_value =(buff[0])*100/4096;
return filter_sred(adc_value,buf_ADC,&FLT);

}


    unsigned short int  filter_sred(unsigned short int ADC_val,unsigned short int* buf, FILTER_REG* filter_reg){
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







