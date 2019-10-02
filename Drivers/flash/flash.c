#include"flash.h"
#include"stm32f1xx.h"

//pageAddress - любой адрес, принадлежащий стираемой странице
void Internal_Flash_Erase(unsigned int pageAddress) {
	while (FLASH->SR & FLASH_SR_BSY);
	if (FLASH->SR & FLASH_SR_EOP) {
		FLASH->SR = FLASH_SR_EOP;
	}

	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = pageAddress;
	FLASH->CR |= FLASH_CR_STRT;
	while (!(FLASH->SR & FLASH_SR_EOP));
	FLASH->SR = FLASH_SR_EOP;
	FLASH->CR &= ~FLASH_CR_PER;
}


void Internal_Flash_Write(uint8_t* data, uint32_t address, uint16_t count) {
	uint32_t i;
Internal_Flash_Erase(address);
	while (FLASH->SR & FLASH_SR_BSY);
	if (FLASH->SR & FLASH_SR_EOP) {
		FLASH->SR = FLASH_SR_EOP;
	}

	FLASH->CR |= FLASH_CR_PG;

	for (i = 0; i < count; i += 2) {
        *(volatile uint16_t*)(address + i) = (((uint16_t)data[i + 1]) << 8) + (uint16_t)data[i];
		while (!(FLASH->SR & FLASH_SR_EOP));
		FLASH->SR = FLASH_SR_EOP;
	}

	FLASH->CR &= ~(FLASH_CR_PG);
}

eep_t flash_read(const uint32_t address) {
    return (*(__IO eep_t*) address);
}




