#include "stm32f10x.h"
#include "stdint.h"
#include "core_cm3.h"
#include "clock.h"
#include "line.h"
#include "obstacle.h"
#include "LCD.h"

#define GO_FORWARD 0x00002400
#define GO_RIGHT 0x00001400
#define GO_LEFT 0x00002800
#define GO_REVERSE 0x00001800

void change_pwm (uint16_t a);
void motorConfigLine(uint16_t direction);
void motorConfigRoom();
void cornerRoutineLEFT(uint16_t direction);
void cornerRoutineRIGHT(uint16_t direction);
void turn180();