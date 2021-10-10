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
#include "CmdMode.h"
#include "CommandExecutor.h"



class CommandClass
{
protected:
	
	int commandLength;
	int currentCommandIndex;
	CmdMode name = NONE;
	bool available = false;
	bool started = false;
	bool disposed = false;

	int commandArgument[CMD_MAX_LENGTH] = { 0 };
	char* id;

	int maxArgumentIndex();
	void setId();
public:
	int lastStatus;
	long lastUpdated;

	CommandClass(CmdMode name);
	CommandClass(int name);

	void setSize(int size);
	void init();
	void dispose();

	virtual void reset();
	bool incrementCommandIndex();
	virtual void appendCommandArgument(int argumentItem);
	virtual char* execute();
	virtual bool update();

	int* getArguments();
	int getMaxCommandIndex();
	int getSize();
	int getCurrentCommandIndex();
	CmdMode getCommandName() { return name; }
	char* getId();
	bool isAvailable();
	bool isExecutable();
	bool isStarted();
	bool isDisposed();
	virtual bool isComplete();

};

extern CommandClass Command;

#endif

