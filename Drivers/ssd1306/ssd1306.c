#include"ssd1306.h"
#include"i2c.h"

static void ssd1306_send(uint8_t control_byte, uint8_t data);

void ssd1306_init(void)
{


    ssd1306_SendCommand(SSD1306_DISPLAY_OFF);
    ssd1306_SendCommand(SSD1306_SET_DISPLAY_CLOCK_DIV);
    ssd1306_SendCommand(0x80);
    ssd1306_SendCommand(SSD1306_SET_MULTIPLEX_RATIO);
    ssd1306_SendCommand(0x3F);
    ssd1306_SendCommand(SSD1306_SET_DISPLAY_OFFSET);
    ssd1306_SendCommand(0x00);
    ssd1306_SendCommand(SSD1306_SET_START_LINE | 0x00);
    ssd1306_SendCommand(SSD1306_SET_CHARGE_PUMP);
    ssd1306_SendCommand(0x14);
    ssd1306_SendCommand(SSD1306_MEMORY_ADDRESS_MODE);
    ssd1306_SendCommand(SSD1306_SET_LCOL_START_ADDRESS);
    ssd1306_SendCommand(SSD1306_SEGMENT_REMAP | 0x01);
    ssd1306_SendCommand(SSD1306_COM_SCAN_INVERSE);
    ssd1306_SendCommand(SSD1306_SET_COM_PINS_CONFIG);
    ssd1306_SendCommand(0x12);
    ssd1306_SendCommand(SSD1306_SET_CONTRAST);
    ssd1306_SendCommand(0xf0);
    //	ssd1306_SendCommand(0x10);
    ssd1306_SendCommand(SSD1306_SET_PRECHARGE_PERIOD);
    ssd1306_SendCommand(0xF1);
    ssd1306_SendCommand(SSD1306_SET_VCOM_DESELECT_LVL);
    ssd1306_SendCommand(0x40);
    ssd1306_SendCommand(SSD1306_ENTIRE_DISPLAY_RESUME);
    ssd1306_SendCommand(SSD1306_NORMAL_DISPLAY);
    ssd1306_FillDisplay(0xff);
    ssd1306_SendCommand(SSD1306_DISPLAY_ON);
}
void ssd1306_SendCommand(unsigned char command)
{

    ssd1306_send(SSD1306_COMMAND_MODE, command);



}


void 	ssd1306_send(uint8_t control_byte, uint8_t data)
{


    d_I2C_Start;


    while (!d_I2C_StartEnd)
    {
    }
    d_I2C_SR1_Clear;



    d_I2C_Byte(SSD1306_ADDRESS);

    while (!(d_I2C_AdrSendEnd))
    {
    }
    d_I2C_SR1_Clear;
    d_I2C_SR2_Clear;

    d_I2C_Byte(control_byte);
    while (!(d_I2C_ByteSendEnd))
    {
    }

    d_I2C_Byte(data);


    while (!(d_I2C_WaitByteTransfer))
    {
    }
    d_I2C_Stop;


}




void ssd1306_SendData(uint8_t *data, uint8_t count)
{
    uint8_t index=0;
    d_I2C_Start;


    while (!d_I2C_StartEnd)
    {
    }
    d_I2C_SR1_Clear;



    d_I2C_Byte(SSD1306_ADDRESS);

    while (!(d_I2C_AdrSendEnd))
    {
    }
    d_I2C_SR1_Clear;
    d_I2C_SR2_Clear;


    d_I2C_Byte(SSD1306_DATA_MODE);
    while (!(d_I2C_ByteSendEnd))
    {
    }

    for(index=0;index<=count-1;index++)
    {
        d_I2C_Byte(*data++) ;
        while (!(d_I2C_ByteSendEnd))
        {
        }
    }

    while (!(d_I2C_WaitByteTransfer))
    {
    }
    d_I2C_Stop;

}


static void ssd1306_SetCursor(unsigned char x, unsigned char p)
{
    ssd1306_SendCommand(SSD1306_SET_LCOL_START_ADDRESS | (x & 0x0F));
    ssd1306_SendCommand(SSD1306_SET_HCOL_START_ADDRESS | (x >> 4));
    ssd1306_SendCommand(SSD1306_SET_PAGE_START_ADDRESS | p);
}

static uint8_t ssd1306_buf1[128];

void ssd1306_FillDisplay(unsigned char data)
{
    unsigned char page, x;


    for (page=0; page<8; page++)
    {
        ssd1306_SetCursor(0, page);
        for (x=0; x<SSD1306_WIDTH; x++)
        {
            ssd1306_buf1[x] = data;
        };
        ssd1306_SendData(ssd1306_buf1, SSD1306_WIDTH );
    };
    ssd1306_SetCursor(0, 0);

}

