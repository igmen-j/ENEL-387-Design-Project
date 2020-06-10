 #include "obstacle.h"
 #include "clock.h"
 
/*
Checks if an obstacle is detected within 25 cm
Displays the current distance in the LCD
*/
uint16_t checkObstacle()
{
	char result[50];
	float distance_front=0, distance_right=0, distance_left=0;
	
	distance_front = obsFront();
	
	commandToLCD(LCD_LN2);
	sprintf(result, "%.1f cm      ",  distance_front);
	str2lcd(result);
	
	delay(600);
	
	
	if (distance_front <= 25)	//object is detected
	{
		return 1;
	}
	
	return 0;	
} 

/*
Checks if an obstacle is detected and returns a length
*/
uint16_t obsFront()
{
	uint32_t time_front=0;
	float distance_front=0;
	
	GPIOC->ODR |= GPIO_ODR_ODR13;
	delay(12);
	GPIOC->ODR &= ~GPIO_ODR_ODR13;
	delay(60);	 
	while(!(GPIOD->IDR & GPIO_IDR_IDR2));	//front side
	while (GPIOD->IDR & GPIO_IDR_IDR2)
	{
		time_front++;
		delay(6);
	}
	
	distance_front = (time_front * 0.034);
	
	return distance_front;
}