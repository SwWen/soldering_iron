#include"i2c.h"
//____Макросы для работы с I2C



void i2c_init(void){

    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //Включаем тактирование Шины и GPIOB
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    GPIOB->CRL |= GPIO_CRL_MODE6 | GPIO_CRL_MODE7 | GPIO_CRL_CNF6 | GPIO_CRL_CNF7;
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;
    I2C1->CR2 &= ~I2C_CR2_FREQ;
    I2C1->CR2 |= 8;
    I2C1->CCR &= ~I2C_CCR_CCR;
    I2C1->CCR = 40;
    I2C1->TRISE = 9;
    I2C1->CR1 |= I2C_CR1_ACK;
    I2C1->CR1 |= I2C_CR1_PE;
    I2C1->CR1 |= I2C_CR1_START;


}






