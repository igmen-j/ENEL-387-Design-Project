#include "stm32f10x.h"
#include "stdint.h"
#include "core_cm3.h"
#include "LCD.h"

#include <stdint.h>


uint16_t detectLine();
void readADC(float ir[]);
void getADCValue(uint32_t ir1, uint32_t ir3, uint32_t ir5);
void countLine();