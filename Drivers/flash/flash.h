#ifndef FLASH_H_INCLUDED
#define FLASH_H_INCLUDED
#define FLASH_PAGE_63   0x800FC00 // 63*1024+shift
#include"stm32f1xx.h"

typedef struct flash {
    uint8_t var1;
    uint8_t var2;
    uint8_t var3;
    uint8_t var4;
} eep_t;


#define flash_write(FLASH_PAGE) (Internal_Flash_Write((uint8_t*)&flash,(FLASH_PAGE),sizeof(flash)));
//void write_flash(eep_t *data);
void Internal_Flash_Write(uint8_t* data, uint32_t address, uint16_t count);
eep_t flash_read(uint32_t address);
#endif // FLASH_H_INCLUDED
