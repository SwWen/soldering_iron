

#include"rcc.h"
void rcc_init()
{
    unsigned long int TimeOut = 10000;
    //Запустить HSE
    RCC->CR   |=  RCC_CR_HSEON;            //Включить генератор HSE
    while((RCC->CR & RCC_CR_HSERDY)==0)    //Ожидание готовности HSE
        if(TimeOut) TimeOut--;
    if(TimeOut==0) return;               //Ошибка!!! Генератор HSE не запустился
    RCC->CR   |=  RCC_CR_CSSON;            //Разрешить работу системы защиты сбоя HSE
    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;       //Не использовать делитель HSE
    //Частота  SystemCoreClock выше 24 MHz - разрешить буфер предварительной выборки FLASH
    FLASH->ACR|=  FLASH_ACR_PRFTBE;        //Включить буфер предварительной выборки
    FLASH->ACR&= ~FLASH_ACR_LATENCY;       //Очистить FLASH_ACR_LATENCY
    FLASH->ACR |= FLASH_ACR_LATENCY_2;     //Пропускать 2 такта
    //Настройка PLL
    RCC->CFGR  |= RCC_CFGR_PLLSRC;         //Источником сигнала для PLL выбран HSE
    RCC->CR   &= ~RCC_CR_PLLON;            //Отключить генератор PLL
    RCC->CFGR &= ~RCC_CFGR_PLLMULL;        //Очистить PLLMULL
    RCC->CFGR |=  RCC_CFGR_PLLMULL4;       //Коефициент умножения = 9
    RCC->CR   |=  RCC_CR_PLLON;            //Включить генератор PLL
    while((RCC->CR & RCC_CR_PLLRDY)==0) {} //Ожидание готовности PLL
    //Переключиться на тактирование от PLL
    RCC->CFGR &= ~RCC_CFGR_SW;             //Очистка битов выбора источника тактового сигнала
    RCC->CFGR |=  RCC_CFGR_SW_PLL;         //Выбрать источником тактового сигнала PLL
    while((RCC->CFGR&RCC_CFGR_SWS)!=0x08) {} //Ожидание переключения на PLL
    //Настроить делитель для шины APB1
    RCC->CFGR &= ~RCC_CFGR_PPRE1;          //Очистка битов предделителя "APB1 Prescaler"
    RCC->CFGR |=  RCC_CFGR_PPRE1_DIV4;     //Установить "APB1 Prescaler" равным 4
    //Настроить делитель для шины APB2
    RCC->CFGR &= ~RCC_CFGR_PPRE2;          //Очистка битов предделителя "APB2 Prescaler"
    RCC->CFGR |=  RCC_CFGR_PPRE2_DIV4;     //Установить "APB2 Prescaler" равным 4
}
