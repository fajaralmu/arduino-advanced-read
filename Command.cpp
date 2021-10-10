// 
// 
// 

#include "Command.h"
#include "InputParses.h"
//#include <Arduino.h>

void CommandClass::setId()
{
	char char_arr[100];
	sprintf(char_arr, "%d", (rand() % 100 + 100));
	this->id = char_arr;
}

int CommandClass::maxArgumentIndex()
{
	return this->commandLength - 1;
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

void CommandClass::setSize(int size)
{
	this->commandLength = size;
	if (size == 0) {
		this->available = true;
	}
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
	//
}

char* CommandClass::execute()
{
	started = true;
	return "<OK>";
}

int* CommandClass::getArguments()
{
	return this->commandArgument;
}

int CommandClass::getMaxCommandIndex()
{
	return this->getSize() - 1;
}

int CommandClass::getSize()
{
	return this->commandLength;
}

int CommandClass::getCurrentCommandIndex()
{
	return this->currentCommandIndex;
}

char* CommandClass::getId()
{
	return this->id;
}

bool CommandClass::isAvailable()
{
	return this->available;
}

bool CommandClass::isExecutable()
{
	return !this->isStarted() && this->available && this->isComplete();
}

bool CommandClass::isStarted()
{
	return this->started;
}
bool CommandClass::isDisposed()
{
	return this->disposed;
}

bool CommandClass::isComplete()
{
	return this->currentCommandIndex == this->maxArgumentIndex();
}



