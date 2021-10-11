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
#include "GlobalMy.h"
#include "CmdMode.h"
#ifdef __cplusplus
extern "C" {
#endif
	
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

