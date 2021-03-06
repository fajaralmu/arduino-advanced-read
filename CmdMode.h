// CmdMode.h

#ifndef _CMDMODE_h
#define _CMDMODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

typedef enum
{
	NONE = 48,
	ALARM = 1,
	PRINT_CHAR = 49,
	PRINT_NUMBER =50,
	LED_ON = 51, // 3
	LED_OFF = 52, // 4
	LED_BLINK = 54, // 6
	STOP_COMMAND = 53, // 5
	MOVE_SERVO = 56,
	READ_SERVO = 57,
	MOVE_MOTOR = 58,
  STOP_MOTOR = 60,
	READ_MOTOR = 59
} CmdMode;

#endif
