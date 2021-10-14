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


#endif

