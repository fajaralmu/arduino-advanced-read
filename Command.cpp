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
	this->currentCommandIndex	= -1;
	this->lastStatus			= 0;
	this->createdAt				= millis();
	this->lastUpdated			= millis();
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

	if (false == incrementCommandIndex() || 
		this->currentCommandIndex == lastIndex)
	{
		return;
	}
	this->commandArgument[this->currentCommandIndex] = argumentItem;

	if (isComplete())
	{
		this->available = true;
	}
}

CommandPayload* CommandClass::buildCommandPayload()
{

	CommandPayload* payload = new CommandPayload();
  	payload->cmdName      	= this->cmdName;
	payload->createdAt		= this->getCreatedAt();
	payload->hardwarePin	= this->commandArgument[0];
	payload->lastStatus		= &this->lastStatus;
	payload->lastUpdated	= &this->lastUpdated;
	
	if (this->cmdName == MOVE_MOTOR)
	{
		payload->input1Pin = this->commandArgument[1];
		payload->input2Pin = this->commandArgument[2];
		payload->speed     = this->commandArgument[3];
		payload->forward   = this->commandArgument[4];
	}
	else
	{
		payload->durationMs = this->commandArgument[1] * 1000;
		payload->intervalMs = this->commandArgument[2] * 1000;
		payload->angle 		= this->commandArgument[3];
	}
	return payload;
}

bool CommandClass::update()
{
	CommandPayload*  payload = buildCommandPayload();
	bool availableToContinue = updateCommand( payload );

	if (!availableToContinue)
	{
		dispose();
	}

	delete payload;
	return availableToContinue;
}

int CommandClass::execute()
{
	this->started = true;

	CommandPayload*  payload = buildCommandPayload();
	int result = executeCommand( payload );

	delete payload;
	return result;
}


bool CommandClass::isExecutable()
{
	return isStarted() == false && this->available == true && isComplete();
}


bool CommandClass::isComplete()
{
	return currentCommandIndex == getMaxCommandIndex();
}
