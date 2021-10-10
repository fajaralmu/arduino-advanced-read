// 
// 
// 

#include "Commandv2.h"

int Cmd_getMaxArgumentIndex(Commandv2* me)
{
	return me->commandLength - 1;
}
void Cmd_setId(Commandv2* me)
{
	char char_arr[100];
	sprintf(char_arr, "%d", (rand() % 100 + 100));
	me->id = char_arr;
}
void Cmd_ctor2(Commandv2* me, CmdMode name)
{
	me->commandName = name;
	Cmd_setId(me);
	Cmd_init(me);
}
void Cmd_ctor(Commandv2* me, int name)
{
	CmdMode commandName = (name);
	me->commandName = commandName;
	Cmd_setId(me);
	Cmd_init(me);
}

int Cmd_setSize(Commandv2* me, int size)
{
	me->commandLength = size;
	return me->commandLength;
}
void Cmd_init(Commandv2* me)
{
	me->currentCommandIndex = -1;
	me->started = 0;
	me->disposed = 0;
	me->lastStatus = 0;
	me->lastUpdated = millis();
	me->commandLength = 0;
	me->currentCommandIndex = 0;
}

void Cmd_reset(Commandv2* me)
{
	me->available = 0;
	me->commandLength = 0;
	memset(me->commandArgument, 0, CMD_MAX_LENGTH);
}
void Cmd_incrementCommandIndex(Commandv2* me)
{
	if (me->currentCommandIndex >= CMD_MAX_LENGTH) {
		//Serial.println("Argument length invalid");
		return;
	}
	me->currentCommandIndex = me->currentCommandIndex + 1;
}
void Cmd_appendCommandArgument(Commandv2* me, int argumentItem)
{
	int lastIndex = me->currentCommandIndex;
	Cmd_incrementCommandIndex(me);
	if (me->currentCommandIndex == lastIndex) return;
	me->commandArgument[me->currentCommandIndex] = argumentItem;

	if (Cmd_isComplete(me))
	{
		me->available = 1;
	}
}
char* Cmd_execute(Commandv2* me)
{
	me->started = 1;
	return "ok";
	// MOVED to processv3.cpp return executeCommand(me->commandName, me->commandArgument, Cmd_getSize(me));
}

int Cmd_getSize(Commandv2* me)
{
	return me->commandLength;
}
int Cmd_getCurrentCommandIndex(Commandv2* me)
{
	return me->currentCommandIndex;
}
CmdMode Cmd_getCommandName(Commandv2* me)
{
	return me->commandName;
}
char* Cmd_getId(Commandv2* me)
{
	return me->id;
}
boolean Cmd_isAvailable(Commandv2* me)
{
	return me->available;
}
boolean Cmd_isExecutable(Commandv2* me)
{
	return 0 == Cmd_isDisposed(me) && 0 == Cmd_isStarted(me) && Cmd_isAvailable(me) && Cmd_isComplete(me);
}
boolean Cmd_isStarted(Commandv2* me)
{
	return me->started;
}
boolean Cmd_isDisposed(Commandv2* me)
{
	return me->disposed;
}
boolean Cmd_isComplete(Commandv2* me)
{
	return Cmd_getCurrentCommandIndex(me) == Cmd_getMaxArgumentIndex(me);
}

void Cmd_update(Commandv2* me)
{
//MOVED to processv3.cpp
//	updateCommand(me->commandName, &me->lastUpdated, &me->lastStatus, me->commandArgument, Cmd_getSize(me));
}
 
void Cmd_dispose(Commandv2* me)
{
	me->disposed = 1;
}
 
