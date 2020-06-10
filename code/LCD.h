#include "stm32f10x.h"
#include "stdint.h"
#include "core_cm3.h"

#define LCD_8B2L 0x38 // ; Enable 8 bit data, 2 display lines
#define LCD_DCB 0x0F // ; Enable Display, Cursor, Blink
#define LCD_MCR 0x06 // ; Set Move Cursor Right
#define LCD_CLR 0x01 // ; Home and clear LCD
#define LCD_LN1 0x80 // ;Set DDRAM to start of line 1
#define LCD_LN2 0xC0 // ; Set DDRAM to start of line 2

// Control signal manipulation for LCDs on 352/384/387 board
// PB0:RS PB1:ENA PB5:R/W*
#define LCD_CM_ENA 0x00210002 //
#define LCD_CM_DIS 0x00230000 //
#define LCD_DM_ENA 0x00200003 //
#define LCD_DM_DIS 0x00220001 //

void LCD_init(void);
void LCD_IO_init (void);

void commandToLCD(uint8_t data);
void dataToLCD(uint8_t data);

void LCDdelay(uint32_t count);

void reg_out( uint32_t reg_data);
uint8_t to_ascii (uint8_t val);
float hexToDec(uint16_t val, int choice);
void str2lcd(char * message);