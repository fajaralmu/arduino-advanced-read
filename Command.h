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
#include "CommandPayload.h"
#include "CommandExecutor.h"



class CommandClass
{
protected:
	
	int commandLength = -1;
	int currentCommandIndex;
	CmdMode cmdName = NONE;
	bool available = false;
	bool started = false;
	bool disposed = false;

	int commandArgument[CMD_MAX_LENGTH] = { 0 };
	char* id;
	
	int lastStatus;
	long createdAt;
	long lastUpdated;

	void setId();
	CommandPayload* buildCommandPayload();
	bool incrementCommandIndex();
	virtual void reset();
	void dispose();
	void init();

public:

	CommandClass(CmdMode name);
	CommandClass(int name);
	~CommandClass();
	
	virtual void appendCommandArgument(int argumentItem);
	virtual char* execute();
	virtual bool update();

	int* getArguments() { return commandArgument; }
	int getMaxCommandIndex() { return getSize() - 1; }
	
	void setSize(int size) { commandLength = size; if (size == 0) available = true; }
	int getSize() { return commandLength; }

	int getCurrentCommandIndex() { return currentCommandIndex; }
	CmdMode getCommandName() { return cmdName; }
	char* getId() { return id; }
	bool isAvailable() { return available; }
	bool isStarted() { return started; }
	bool isDisposed() { return disposed; }
	int getLastStatus() { return lastStatus; }
	long getLastUpdated() { return lastUpdated; }
	long getCreatedAt() { return createdAt; }

	virtual bool isExecutable();
	virtual bool isComplete();

};

extern CommandClass Command;

#endif

