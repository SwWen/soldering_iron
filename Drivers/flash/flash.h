#ifndef FLASH_H_INCLUDED
#define FLASH_H_INCLUDED
#define FLASH_PAGE_63   0x800FC00 // 63*1024+shift
#include"stm32f1xx.h"

typedef struct {
    uint8_t set[4];
    uint16_t param[10];
} eep_t;



//void write_flash(eep_t *data);
void Internal_Flash_Write(uint8_t* data, uint32_t address, uint16_t count);
eep_t flash_read(const uint32_t address);
#endif // FLASH_H_INCLUDED
