#include "LCD.h"

void LCD_init(void)
{
		commandToLCD(LCD_8B2L);
		LCDdelay(30000);
		commandToLCD(LCD_8B2L);
		LCDdelay(6000);
		commandToLCD(LCD_8B2L);
		
		commandToLCD(LCD_8B2L);
		commandToLCD(LCD_DCB);
		commandToLCD(LCD_CLR);
		commandToLCD(LCD_MCR);
}

void LCD_IO_init (void)
{
		RCC->APB2ENR |=  RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN;
	
		GPIOB->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE5;
    GPIOB->CRL &= ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF5;

    GPIOC->CRL = 0x33333333;
}
	
/*
* Name: commandToLCD
* Type: PUBLIC
* Parameters: a single byte of command information for the LCD controller
* Returns: nothing
* Description: This function generates control timing and data signals to send one command byte to the LCD
*/
void commandToLCD(uint8_t data)
{
		GPIOB->BSRR = LCD_CM_ENA; //RS low, E high
		// GPIOC->ODR = data; //BAD: may affect upper bits on port C
		GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
		GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
		LCDdelay(8000);
		GPIOB->BSRR = LCD_CM_DIS; //RS low, E low
		LCDdelay(80000);
}

void dataToLCD(uint8_t data)
{
		GPIOB->BSRR = LCD_DM_ENA; //RS low, E high
		// GPIOC->ODR = data; //BAD: may affect upper bits on port C
		GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
		GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
		LCDdelay(8000);
		GPIOB->BSRR = LCD_DM_DIS; //RS low, E low
		LCDdelay(80000);
}

void LCDdelay(uint32_t count)
{
    int i=0;
    for(i=0; i< count; ++i)
    {
    }
}


void reg_out( uint32_t reg_data)
{
		int i;
		uint32_t shifted_val;
		uint8_t print_val;
		//dataToLCD (0x30);
		//dataToLCD (0x78);
		//for ( i=28; i >= 0 ; i = (i-4))
		//{
			//shifted_val = (reg_data >> i) & 0xf;
			print_val = (to_ascii (shifted_val));
			//print_val = (hexToDec (shifted_val, 0));
			dataToLCD(print_val);
		//}
		dataToLCD(0x20);
}

float hexToDec(uint16_t val, int choice)
{
	float sum;
	uint16_t a = val & 0xF;
	uint16_t b = (val & 0xF0) >> 4;
	uint16_t c = (val & 0xF00) >> 8;
	uint16_t d = (val & 0xF000) >> 12;
	
	b *= 16;
	c *= 16*16;
	d *= 16*16*16;
	
	if (choice == 1)
	{
		return sum = (a + b + c + d) * 0.0007;
	}
	else 
	{
		return sum = (a + b + c + d) * 0.07;
	}
}

void str2lcd(char * message)
{
	int i = 0;
	uint16_t messagelength = strlen(message);
	for (int i = 0; i < messagelength; i++)
	{
		dataToLCD(*message);
		++message;		
	}
}
	


uint8_t to_ascii(uint8_t val)
{
	if (val <= 9)
		return 0x30+val;
	else if (val == 0xA)
		return 0x41;
	else if (val == 0xB)
		return 0x42;
	else if (val == 0xC)
		return 0x43;
	else if (val == 0xD)
		return 0x44;
	else if (val == 0xE)
		return 0x45;
	else if (val == 0xF)
		return 0x46;
}