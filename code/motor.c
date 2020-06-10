#include "motor.h"

int homeCount = 0;	//global variable to check if robot is at home

/*
If an obstacle is detected, robot will stop, turn 180 degrees, and get on with its life
*/
void motorConfigRoom()
{
	char result[50];
	float distance_front, distance_turn;
	
	GPIOB->ODR = 0;
	delay(1800000);
	
	change_pwm(50);

	commandToLCD(LCD_LN2);
	sprintf(result, "%.1f cm      ",  distance_front);
	str2lcd(result);
	turn180();
}

/*
Determines how the robot moves
direction:
1 = forward
2 = reverse
3 = right
4 = right and on a corner
5 = left
6 = left and on a corner

>= 2.5 : White line is detected
< 2.5 : Black line is detected

*/
void motorConfigLine(uint16_t direction)
{
	float ir_dec[3];
	if (direction == 1)	//forward
	{
		change_pwm(33);
		GPIOB->ODR = GO_FORWARD; 
		readADC(ir_dec);
		if ((ir_dec[0] >= 2.5) && (ir_dec[1] >= 2.5) && (ir_dec[2] >= 2.5))
		{
				homeCount++;
			change_pwm(25);
			str2lcd("HOME      ");
			if (homeCount == 2)
			{
					str2lcd("HOME STOP     ");
					GPIOB->ODR = 0;
					delay (990000000);
			}
		}
		change_pwm(33);
	}
	else if (direction == 2)	//reverse
	{
		change_pwm(33);
		float ir_dec[3];
		ir_dec[1] = 0;
				
		while ((ir_dec[0] <= 2.5) && (ir_dec[1] <= 2.5) && (ir_dec[1] <= 2.5))
		{
			GPIOB->ODR = GO_REVERSE;
			readADC(ir_dec);
		}
		GPIOB->ODR = 0;
		delay(12000);
	}
		else if (direction == 3)	//right
	{
		change_pwm(60);
		float ir_dec[3];
		ir_dec[1] = 0;
		
		while (ir_dec[0] <= 2.5)
		{
			GPIOB->ODR = GO_RIGHT;
			readADC(ir_dec);
		}
		GPIOB->ODR = 0;	// test maybe remove this later
	}
	else if (direction == 5)	//left
	{
		change_pwm(60);
		float ir_dec[3];
		ir_dec[1] = 0;
				
		while (ir_dec[1] <= 2.5)
		{
			GPIOB->ODR = GO_LEFT;
			readADC(ir_dec);			
		}
		GPIOB->ODR = 0;
	}
	else if (direction == 6)	//left corner
	{
		change_pwm(50);
		cornerRoutineLEFT(direction);
	}
	else if (direction == 4)	//right corner
	{
		change_pwm(50);
		cornerRoutineRIGHT(direction);
	}
	else
	{
		GPIOB->ODR = 0;
	}
	
}

/*
With turn left until the sensors are in this fashion: 110
*/
void cornerRoutineLEFT(uint16_t dir)
{
	int count = 0;
	
	float ir_dec[3];
	ir_dec[0] = 5;
	ir_dec[1] = 5;
	ir_dec[2] = 0;
	
	GPIOB->ODR = 0;
	
	while ((ir_dec[0] >= 2.5) && (ir_dec[1] >= 2.5) && (ir_dec[2] < 2.5))
	{
		GPIOB->ODR = GO_LEFT;
		readADC(ir_dec);
	}		
	GPIOB->ODR = 0;
	delay(6000);
}

/*
With turn right until the sensors are in this fashion: 011
*/
void cornerRoutineRIGHT(uint16_t dir)
{
	int count = 0;
	
	float ir_dec[3];
	ir_dec[0] = 0;
	ir_dec[1] = 5;
	ir_dec[2] = 5;
	
	GPIOB->ODR = 0;
	
	while ((ir_dec[0] < 2.5) && (ir_dec[1] >= 2.5) && (ir_dec[2] >= 2.5))
	{	
		GPIOB->ODR = GO_RIGHT;
		readADC(ir_dec);
	}
		
	GPIOB->ODR = 0;
	delay(6000);
}

/*
Changes the PWM of the motors
Taken from lab
*/
void change_pwm (uint16_t a)
{	
	TIM1->CCR1 = a;	
	TIM1->EGR |= TIM_EGR_UG; // Reinitialize the counter  
}

/*
Routing for turning 180 degrees
Will turn right until left sensor goes HIGH
This forces the middle sensor to go LOW

To actually turn 180, it will turn right while until middle sensor goes HIGH
*/
void turn180()
{
	float ir_dec[3];
	ir_dec[0] = 0;
	ir_dec[1] = 0;
	ir_dec[2] = 0;
	
	while (ir_dec[0] <= 2.5)
	{
		GPIOB->ODR = GO_RIGHT;
		readADC(ir_dec);
		str2lcd("TURN 180       ");
	}
	
	while (ir_dec[1] <= 2.5)
	{
		GPIOB->ODR = GO_RIGHT;
		readADC(ir_dec);
		str2lcd("TURN 180       ");
	}
	
	GPIOB->ODR = 0;
	delay(1200000);
	
	
}