// 
// 
// 

#include "Command.h"
#include "InputParses.h"
#include <Arduino.h>

int running_id = 1;

CommandClass::CommandClass(CommandName name)
{
	running_id++;
	this->name = name;
	this->id = running_id;
	init();
}
CommandClass::CommandClass(int name)
{
	running_id++;
	this->name = static_cast<CommandName>(name);
	this->id = running_id++;
	init();

}
void CommandClass::init()
{
	currentCommandIndex = -1;
	Serial.println("INIT Commands");
}

void CommandClass::reset()
{
	available = false;
	commandLength = 0;
	memset(commandArgument, 0, CMD_MAX_LENGTH);
}

void CommandClass::incrementCommandIndex()
{
	this->currentCommandIndex = this->currentCommandIndex + 1;
}

void CommandClass::appendCommandArgument(int argumentItem)
{
	incrementCommandIndex();
	commandArgument[currentCommandIndex] = argumentItem;
	Serial.print(" >> Append arg:");
	Serial.print(argumentItem, DEC);
	Serial.print(" Cmd index:");
	Serial.println(currentCommandIndex, DEC);

	if (isComplete()) {
		Serial.println(" .. complete .. ");
		Serial.println();
		available = true;
	}
}

char* CommandClass::execute()
{
	disposed = true;
	char* ch = printNumbers(commandArgument, commandLength);
	return ( ch );
}

bool CommandClass::isAvailable()
{
	return this->available;
}

bool CommandClass::isExecutable()
{
	return !this->isDisposed() && this->available && this->isComplete();
}

bool CommandClass::isDisposed()
{
	return this->disposed;
}

bool CommandClass::isComplete()
{
	return this->currentCommandIndex == this->commandLength - 1;
}



