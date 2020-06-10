#include "stm32f10x.h"
#include "stdint.h"
#include "core_cm3.h"
#include "clock.h"
#include "LCD.h"

uint16_t checkObstacle();
uint16_t obsFront();
uint16_t obsLeft();
uint16_t obsRight();