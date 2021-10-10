// Command.h

#ifndef _COMMAND_h
#define _COMMAND_h

#define CMD_MAX_LENGTH	255

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Arduino.h>
#include "CommandName.h"
#include "CommandExecutor.h"



class CommandClass
{
protected:
	
	int commandLength;
	int currentCommandIndex;
	CommandName name = NONE;
	bool available = false;
	bool disposed = false;
	int commandArgument[CMD_MAX_LENGTH] = { 0 };
	int id = 0;
public:
	CommandClass(CommandName name);
	CommandClass(int name);

	void setSize(int size) { this->commandLength = size; }
	void init();

	virtual void reset();
	virtual void incrementCommandIndex();
	virtual void appendCommandArgument(int argumentItem);
	virtual char* execute();

	int getSize() { return this->commandLength; }
	int getCurrentCommandIndex() { return currentCommandIndex; }
	CommandName getCommandName() { return name; }
	int getId() { return id; }
	bool isAvailable();
	bool isExecutable();
	bool isDisposed();
	virtual bool isComplete();

};

extern CommandClass Command;

#endif

