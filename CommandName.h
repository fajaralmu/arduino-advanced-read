// CommandName.h

#ifndef _COMMANDNAME_h
#define _COMMANDNAME_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum CommandName
{
	NONE			= 0,
	ALARM			= 1,
	PRINT_CHAR		= 2,
	PRINT_NUMBER	= 3,
};

#endif

