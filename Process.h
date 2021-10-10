// Process.h

#ifndef _PROCESS_h
#define _PROCESS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif
#include "InputParses.h"
#include "CommandExecutor.h"
#include "Command.h"
#include "Commandv2.h"

#ifdef __cplusplus
extern "C" {
#endif
	void preProccess();
	void processInput(int input);
	void checkCurrentCommand();
	void applyCommands();

#ifdef __cplusplus
}
#endif

