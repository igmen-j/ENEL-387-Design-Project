#include "line.h"
#include "LCD.h"

/*
Uses ADC
Taken from lab
*/
void readADC(float ir_dec[])
{
	uint32_t ir1, ir3, ir5, direction;
	
	ADC1->SQR3 = 0x1;	//channel 1
	ADC1->CR2 = 0x1;
	while (ADC1->SR == 0);
	ir1 = ADC1->DR;	//ir1
	ir_dec[0] = hexToDec(ir1, 1);
	
	
	ADC1->SQR3 = 0x2;	//channel 2
	ADC1->CR2 = 0x1;
	while (ADC1->SR == 0);
	ir5 = ADC1->DR;	//ir5
	ir_dec[2] = hexToDec(ir5, 1);
	
	
	ADC1->SQR3 = 0x3;	//channel 3
	ADC1->CR2 = 0x1;
	while (ADC1->SR == 0);
	ir3 = ADC1->DR;
	ir_dec[1] = hexToDec(ir3, 1); 
}


/*
This routine determines how the robot will move
Also displays the case on the LCD

7 Cases:

010	: forward
111	: forward
000	: reverse
001	: right
011	: right and corner
100	: left
110	: left and corner

returns a number to communicate with the motors

*/
uint16_t detectLine()
{
	uint32_t direction = 0;
	
	float ir_dec[3], ir1_dec, ir3_dec, ir5_dec;
	
	readADC(ir_dec);
	ir1_dec = ir_dec[0];
	ir3_dec = ir_dec[1];
	ir5_dec = ir_dec[2];
	
	commandToLCD(LCD_LN1);
	
	if ((ir1_dec < 2.5) && (ir3_dec >= 2.5) && (ir5_dec < 2.5))	//010
	{
		str2lcd("FORWARD      ");
		return 1;
	}
	else if ((ir1_dec >= 2.5) && (ir3_dec >= 2.5) && (ir5_dec >= 2.5))	//111
	{
		str2lcd("FORWARD       ");
		return 1;
	}
	else if ((ir1_dec < 2.5) && (ir3_dec < 2.5) && (ir5_dec < 2.5))	//000
	{
		str2lcd("REVERSE        ");
		return 2;
	}
	else if ((ir1_dec < 2.5) && (ir3_dec < 2.5) && (ir5_dec >= 2.5))	//001
	{
		str2lcd("RIGHT       ");
		return 3;
	}
	else if ((ir1_dec < 2.5) && (ir3_dec >= 2.5) && (ir5_dec >= 2.5))	//011
	{
		str2lcd("R CORNER      ");
		return 4;
	}
	else if ((ir1_dec >= 2.5) && (ir3_dec < 2.5) && (ir5_dec < 2.5))	//100
	{
		str2lcd("LEFT        ");
		return 5;
	}
	else if ((ir1_dec >= 2.5) && (ir3_dec >= 2.5) && (ir5_dec < 2.5))	//110
	{
		str2lcd("L CORNER      ");
		return 6;
	}
	return direction;
}