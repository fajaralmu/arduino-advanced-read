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
	_NONE			= 0,
	_ALARM			= 1,
	_PRINT_CHAR		= 2,
	_PRINT_NUMBER	= 3,
};

#endif

