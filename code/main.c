/******************************************************************************
 * Name: 387 Final Project
 * Description: Line tracker, line counter, and obstacle detector robot
 * Also known as: Project Insane Robot, LLO Robot, Robot for the end of the world, Robot2020, 
 *								Robot with a lot of names
 * Version: FINAL
 * Authors: Justin Igmen / Zain Khokhar
 *****************************************************************************/

#include "clock.h"
#include "init.h"
#include "gpio.h"
#include "motor.h"
#include "obstacle.h"
#include "line.h"
#include "LCD.h"
#include "lineCounter.h"

int main()
{
	clockInit();
	gpio_init();
	motorDriverInit();
	pwmInit();
	obstacleSensorInit();
	LCD_IO_init();
	LCD_init();
	lineFollowerInit();
	
	uint16_t mode, obs_dir, line_dir;
	
	while(1)
	{
		mode = SW1();	
		
		//MODE 0000: Course Mode
		if (mode == 0b0000)
		{
			obs_dir = checkObstacle();
			if (obs_dir == 1)
			{
				motorConfigRoom(obs_dir);
			}
			else
			{
				line_dir = detectLine();
				motorConfigLine(line_dir);
			}
		}
		//MODE Anything else: Line tracker mode
		else
		{
			commandToLCD(LCD_LN1);
			str2lcd("LINE COUNT MODE");
			lineCounter();
		}
	}
}

