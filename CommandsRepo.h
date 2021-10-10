// CommandsRepo.h

#ifndef _COMMANDSREPO_h
#define _COMMANDSREPO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Commandv2.h"
#include "CmdMode.h"
#include "GlobalMy.h"

#ifdef __cplusplus
extern "C" {
#endif

	Commandv2** getCommands();
	Commandv2* getCommand(int index);
	void putCommand(Commandv2* cmd, int index);
	void resetCommands();
	void stopByCommandMode(CmdMode mode);
	void setCommandCount(int count);
	int getCommandCount();

#ifdef __cplusplus
}
#endif

#endif

