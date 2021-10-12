// CommandExecutor.h

#ifndef _COMMANDEXECUTOR_h
#define _COMMANDEXECUTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Arduino.h>
#include "GlobalMy.h"
#include "CmdMode.h"
#include "CommandPayload.h"

#ifdef __cplusplus
extern "C" {
#endif

	char* executeCommand(CommandPayload*  payload);

	bool updateCommand(CommandPayload*  payload);

#ifdef __cplusplus
}
#endif

#endif


