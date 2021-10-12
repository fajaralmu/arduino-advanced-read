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
	this->cmdName = name;
	
	setId();
	init();
}

CommandClass::CommandClass(int name)
{
	this->cmdName = static_cast<CmdMode>(name);
	
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
	this->createdAt = millis();
	this->lastUpdated = millis();
}

void CommandClass::dispose()
{
	this->disposed = true;
}

void CommandClass::reset()
{
	this->available = false;
	this->commandLength = 0;
	memset(this->commandArgument, 0, CMD_MAX_LENGTH);
}

bool CommandClass::incrementCommandIndex()
{
	if (currentCommandIndex >= CMD_MAX_LENGTH) {
		return false;
	}
	this->currentCommandIndex = this->currentCommandIndex + 1;
	return true;
}

void CommandClass::appendCommandArgument(int argumentItem)
{
	int lastIndex = this->currentCommandIndex;
	if (!incrementCommandIndex()) return;
	if (this->currentCommandIndex == lastIndex) return;
	this->commandArgument[this->currentCommandIndex] = argumentItem;

	if (isComplete()) {
		this->available = true;
	}
}

CommandPayload* CommandClass::buildCommandPayload()
{
	// 0 -> Hardware PIN
	// 1 -> durationSec
	// 2 -> intervalSec

	CommandPayload* payload = new CommandPayload(this->cmdName);
	payload->createdAt = this->getCreatedAt();
	payload->hardwarePin = this->commandArgument[0];
	payload->durationMs = this->commandArgument[1] * 1000;
	payload->intervalMs = this->commandArgument[2] * 1000;
	payload->lastStatus = &this->lastStatus;
	payload->lastUpdated = &this->lastUpdated;
	return payload;
}

bool CommandClass::update()
{
	CommandPayload*  payload = buildCommandPayload();
	bool availableToContinue = updateCommand(payload);

	if (!availableToContinue)
	{
		dispose();
	}

	delete payload;
	return availableToContinue;
}

char* CommandClass::execute()
{
	this->started = true;

	CommandPayload*  payload = buildCommandPayload();
	char* result = executeCommand( payload );

	delete payload;
	return result;
}


bool CommandClass::isExecutable()
{
	return !isStarted() && this->available == true && isComplete();
}


bool CommandClass::isComplete()
{
	return currentCommandIndex == getMaxCommandIndex();
}



