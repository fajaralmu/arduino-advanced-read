// CommandExecutor.h

#ifndef _COMMANDEXECUTOR_h
#define _COMMANDEXECUTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif
#include <Arduino.h>
#include "InputParses.h"
#include "GlobalMy.h"
#include "CmdMode.h"
#include "CommandsRepo.h"
#ifdef __cplusplus
extern "C" {
#endif
	char* printNumbers(int inputs[], int size);
	char* printCharacters(int inputs[], int size);

	char* executeCommand(
		CmdMode mode, 
		int arguments[], 
		int size);

	bool updateCommand(
		CmdMode cmd, 
		long *lastUpdated, 
		int *lastStatus, 
		int arguments[], 
		int size);

#ifdef __cplusplus
}
#endif

