// Command.h

#ifndef _COMMAND_h
#define _COMMAND_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "GlobalMy.h"
#include <Arduino.h>
#include "CommandName.h"
#include "CommandExecutor.h"



class CommandClass
{
protected:
	
	int commandLength;
	int currentCommandIndex;
	CommandName name = _NONE;
	bool available = false;
	bool disposed = false;
	int commandArgument[CMD_MAX_LENGTH] = { 0 };
	char* id;

	int maxArgumentIndex();
	void setId();
public:
	CommandClass(CommandName name);
	CommandClass(int name);

	void setSize(int size);
	void init();

	virtual void reset();
	virtual void incrementCommandIndex();
	virtual void appendCommandArgument(int argumentItem);
	virtual char* execute();

	int getSize();
	int getCurrentCommandIndex();
	CommandName getCommandName() { return name; }
	char* getId();
	bool isAvailable();
	bool isExecutable();
	bool isDisposed();
	virtual bool isComplete();

};

extern CommandClass Command;

#endif

