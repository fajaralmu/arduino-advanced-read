// 
// 
// 

#include "Command.h"
//#include <Arduino.h>

void CommandClass::setId()
{
	char char_arr[100];
	sprintf(char_arr, "%d", (rand() % 100 + 100));
	this->id = char_arr;
}

CommandClass::CommandClass(CmdMode name)
{
	this->name = name;
	
	setId();
	init();
}


CommandClass::CommandClass(int name)
{
	this->name = static_cast<CmdMode>(name);
	setId();
	init();
}

CommandClass::~CommandClass()
{
}

void CommandClass::init()
{
	this->currentCommandIndex = -1;
	this->lastStatus = 0;
	this->lastUpdated = millis();
	Serial.println("Initialize Commands");
}

void CommandClass::dispose()
{
	this->disposed = true;
}

void CommandClass::reset()
{
	available = false;
	commandLength = 0;
	memset(commandArgument, 0, CMD_MAX_LENGTH);
}

bool CommandClass::incrementCommandIndex()
{
	if (this->currentCommandIndex >= CMD_MAX_LENGTH) {
		return false;
	}
	this->currentCommandIndex = this->currentCommandIndex + 1;
	return true;
}

void CommandClass::appendCommandArgument(int argumentItem)
{
	int lastIndex = currentCommandIndex;
	if (!incrementCommandIndex()) return;
	if (currentCommandIndex == lastIndex) return;
	commandArgument[currentCommandIndex] = argumentItem;

	if (isComplete()) {
		available = true;
	}
}

bool CommandClass::update()
{
	bool availableToContinue = updateCommand(
		getCommandName(),
		&lastUpdated,
		&lastStatus,
		getArguments(),
		getSize());
	if (!availableToContinue)
	{
		dispose();
	}
}

char* CommandClass::execute()
{
	started = true;
	return executeCommand(
		getCommandName(),
		getArguments(),
		getSize());
}


bool CommandClass::isExecutable()
{
	return !this->isStarted() && this->available && this->isComplete();
}


bool CommandClass::isComplete()
{
	return this->currentCommandIndex == this->getMaxCommandIndex();
}



