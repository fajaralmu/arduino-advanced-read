// CommandExecutor.h

#ifndef _COMMANDEXECUTOR_h
#define _COMMANDEXECUTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif
#include "InputParses.h"
#ifdef __cplusplus
extern "C" {
#endif
	char* printNumbers(int inputs[], int size);
	char* printCharacters(int inputs[], int size);

#ifdef __cplusplus
}
#endif

