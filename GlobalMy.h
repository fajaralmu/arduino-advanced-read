// GlobalMy.h

#ifndef _GLOBALMY_h
#define _GLOBALMY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#define CMD_MAX_LENGTH	250
#define LED_PIN			13
#define COMMAND_MAX_COUNT   50
#define SERVO_A_PIN		9
#define SERVO_B_PIN		10
#define SERVO_C_PIN		11

// message transmission

#define START_OF_HEADING	01
#define START_OF_TEXT		02

#define END_OF_TEXT			03
#define END_OF_TRANSMISSION	04


#endif

