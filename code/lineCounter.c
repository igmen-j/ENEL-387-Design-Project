#include "lineCounter.h"

/*
Counts the lines on the floor and displays the number on the LCD
Only counts the rising edge
*/
void lineCounter()
{
	float ir_dec[3], ir;
	char result[50];
	int count = 0, blackCount = 0, binary = 0;
	float oldValue;
	
	readADC(ir_dec);
	change_pwm(25);
	GPIOB->ODR = GO_FORWARD;
	
	while (blackCount <= 10)
	{
//			commandToLCD(LCD_LN1);
//			sprintf(result, "black: %i          ", blackCount);
//			str2lcd(result);
//		while(ir_dec[1] <= 2.5)
//		{
		GPIOB->ODR = GO_FORWARD;
		readADC(ir_dec);
		
		if( ir_dec[1] >= 2.5)
		{
			binary = 1;
			GPIOB->ODR = 0;
			delay(12000000);
			GPIOB->ODR = GO_FORWARD;
		}
		else	
		{
			binary = 0;
			GPIOB->ODR = 0;
			delay(12000000);
			GPIOB->ODR = GO_FORWARD;
		}
		
		if ((binary == 1) && (oldValue != binary))
		{
			count++;
		}
		
		commandToLCD(LCD_LN2);
		sprintf(result, "Count: %i", count);
		str2lcd(result);
		
		oldValue = binary;
		
		if (ir_dec[1] < 2.5)
			blackCount++;
	}
	
	commandToLCD(LCD_LN1);		
	str2lcd("End count                      ");
	str2lcd(result);
	GPIOB->ODR = 0;
	delay(1200000000);
}