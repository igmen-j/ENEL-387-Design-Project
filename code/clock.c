#include "stm32f10x.h"
#include "clock.h"

void clockInit(void)
{
	  uint32_t temp = 0x00;
    //If you hover over the RCC you can go to the definition and then
    //see it is a structure of all the RCC registers.  Then you can
    //simply assign a value.
    RCC->CFGR = 0x00050002;     // Output PLL/2 as MCO,					//WAs ORIGINALLY 0x07050002
                                // PLLMUL X3, PREDIV1 is PLL input

    RCC->CR =  0x01010081;      // Turn on PLL, HSE, HSI
}

void delay(uint32_t count)
{
    int i=0;
    for(i=0; i< count; ++i)
    {
    }
}