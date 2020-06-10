 #include "gpio.h"
 
// SWITCH FUNCTIONS

//Taken from lab
uint16_t SW1(void)
{
		uint16_t sw1_val;
	
	 	sw1_val = ((( GPIOA->IDR & ( GPIO_IDR_IDR6 )) >> 3 ) \
		 | (( GPIOA->IDR & ( GPIO_IDR_IDR7 )) >> 5 ) \
		 | (( GPIOC->IDR & ( GPIO_IDR_IDR10 )) >> 9 ) \
		 | (( GPIOC->IDR & ( GPIO_IDR_IDR11 )) >> 11 )) \
		 & 0x0F;
		return (sw1_val);
}