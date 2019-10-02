#include"gpio.h"

/*
 * GPIOx_CRL, GPIOx_CRH – задают режимы работы каждого из битов порта в качестве входа или выхода, определяют конфигурацию входных и выходных каскадов.
GPIOx_IDR – входной регистр данных для чтения физического состояния выводов порта x.
GPIOx_ODR– выходной регистр осуществляет запись данных непосредственно в порт.
GPIOx_BSRR – регистр атомарного сброса и установки битов порта.
GPIOx_BSR – регистр сброса битов порта.
GPIOx_LCKR – регистр блокировки конфигурации выводов.


MODEy[1:0] = 00: Режим входа (состояние после сброса);
MODEy[1:0] = 01: Режим выхода, максимальная скорость – 10МГц;
MODEy[1:0] = 10: Режим выхода, максимальная скорость – 2МГц;
MODEy[1:0] = 11: Режим выхода, максимальная скорость – 50МГц.

Биты CNF задают конфигурацию выходных каскадов соответствующих выводов:
в режиме входа:
CNFy[1:0] = 00: Аналоговый вход;
CNFy[1:0] = 01: Вход в третьем состоянии (состояние после сброса);
CNFy[1:0] = 10: Вход с притягивающим резистором pull-up (если PxODR=1) или pull-down (если PxODR=0);
CNFy[1:0] = 11: Зарезервировано.

в режиме выхода:
CNFy[1:0] = 00: Двухтактный выход общего назначения;
CNFy[1:0] = 01: Выход с открытым стоком общего назначения;
CNFy[1:0] = 10: Двухтактный выход с альтернативной функцией;
CNFy[1:0] = 11: Выход с открытым стоком с альтернативной функцией.

 */


void gpio_init(void){
    RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
    AFIO -> MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
    RCC->APB2ENR|=RCC_APB2ENR_IOPCEN|RCC_APB2ENR_IOPBEN|RCC_APB2ENR_IOPAEN;
    GPIOC->CRH 	|= GPIO_CRH_MODE13;
    GPIOC->CRH	&= ~GPIO_CRH_CNF13;
    GPIOB->CRL |=GPIO_CRL_MODE;
    GPIOB->CRL &= ~GPIO_CRL_CNF;
    GPIOB->CRH |=GPIO_CRH_MODE8|GPIO_CRH_MODE9|GPIO_CRH_MODE10|GPIO_CRH_MODE11|GPIO_CRH_MODE12;
    GPIOB->CRH &= ~(GPIO_CRH_CNF8|GPIO_CRH_CNF9|GPIO_CRH_CNF10|GPIO_CRH_CNF11|GPIO_CRH_CNF12);
    GPIOA->CRL&= ~(GPIO_CRL_MODE3|GPIO_CRL_MODE4);
    GPIOA->CRL &= ~GPIO_CRL_CNF3;
    GPIOA->CRL &= ~GPIO_CRL_CNF4;
    GPIOA->CRL|=GPIO_CRL_CNF3_1|GPIO_CRL_CNF4_1;
    GPIOA->ODR|=GPIO_ODR_ODR3|GPIO_ODR_ODR4;
}
