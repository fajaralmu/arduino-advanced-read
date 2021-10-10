// Commandv2.h

#ifndef _COMMANDV2_h
#define _COMMANDV2_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "GlobalMy.h"
//#include "CmdMode.h"
#include "CommandExecutor.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
	int commandLength;
	int currentCommandIndex;
	CmdMode commandName;
	boolean available;
	boolean disposed;
	int commandArgument[CMD_MAX_LENGTH];
	char* id;
} Commandv2;


int Cmd_getMaxArgumentIndex(Commandv2* me);
void Cmd_setId(Commandv2* me);
void Cmd_ctor2(Commandv2* me, CmdMode name);
void Cmd_ctor(Commandv2* me, int name);

void Cmd_setSize(Commandv2* me, int size);
void Cmd_init(Commandv2* me);

void Cmd_reset(Commandv2* me);
void Cmd_incrementCommandIndex(Commandv2* me);
void Cmd_appendCommandArgument(Commandv2* me, int argumentItem);
char* Cmd_execute(Commandv2* me);

int Cmd_getSize(Commandv2* me);
int Cmd_getCurrentCommandIndex(Commandv2* me);
CmdMode Cmd_getCommandName(Commandv2* me);
char* Cmd_getId(Commandv2* me);
boolean Cmd_isAvailable(Commandv2* me);
boolean Cmd_isExecutable(Commandv2* me);
boolean Cmd_isDisposed(Commandv2* me);
boolean Cmd_isComplete(Commandv2* me);

#ifdef __cplusplus
}
#endif

#endif

