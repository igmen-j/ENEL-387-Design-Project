#include "stm32f10x.h"
#include "stdint.h"
#include "core_cm3.h"

 //Functions available for public use
	
	uint16_t SW1(void);
	uint16_t read_buttons(void);
	void update_LEDS(uint16_t LED_val);
	