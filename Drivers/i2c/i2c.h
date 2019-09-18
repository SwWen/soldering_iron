#ifndef I2C_H
#define I2C_H
#include"stm32f1xx.h"

#define d_I2C_StartEnd            (I2C1->SR1 & I2C_SR1_SB)      //__Старт сформирован?
#define d_I2C_AdrSendEnd         (I2C1->SR1 & I2C_SR1_ADDR)   //__Адрес отправлен?
#define d_I2C_ByteSendEnd         (I2C1->SR1 & I2C_SR1_TXE)      //__Данные отправлены?
#define d_I2C_WaitBusy      (I2C1->SR2 & I2C_SR2_BUSY)   //__Флаг занятости установлен?
#define d_I2C_WaitByteTransfer      (I2C1->SR1 & I2C_SR1_BTF)   //__Флаг занятости установлен?
#define d_I2C_Start         I2C1->CR1 |= (I2C_CR1_START | I2C_CR1_PE)      //__Сформировать старт I2C2.
#define d_I2C_Stop         I2C1->CR1 |= I2C_CR1_STOP      //__Сформировать стоп I2C2.

#define d_I2C_Byte(Byte)   I2C1->DR = Byte                     //__Байт для отправки.

#define d_I2C_SR2_Clear   (void)I2C1->SR2                     //__Очищает регистр SR2 путем его чтения.
#define d_I2C_SR1_Clear   (void)I2C1->SR1                     //__Очищает регистр SR2 путем его чтения.



void i2c_init(void);
#endif // I2C_H
