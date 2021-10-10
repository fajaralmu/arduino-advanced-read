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
} CmdMode;

#endif

