// 
// 
// 

#include "Command.h"
#include "InputParses.h"
#include <Arduino.h>

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

CommandClass::CommandClass(CommandName name)
{
	this->name = name;
	
	setId();
	init();
}


CommandClass::CommandClass(int name)
{
	this->name = static_cast<CommandName>(name);
	
	setId();
	init();

}
//
//int CommandClass::getId() {
//	return this->id;
//}

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
	if (this->currentCommandIndex >= CMD_MAX_LENGTH) {
		Serial.println("Argument length invalid");
		return;
	}
	this->currentCommandIndex = this->currentCommandIndex + 1;
}

void CommandClass::appendCommandArgument(int argumentItem)
{
	int lastIndex = currentCommandIndex;
	incrementCommandIndex();
	if (currentCommandIndex == lastIndex) return;
	commandArgument[currentCommandIndex] = argumentItem;
	
	Serial.print("(");
	Serial.print(getId());
	Serial.print(")>> Append arg:");
	Serial.print(argumentItem, DEC);
	Serial.print(" Cmd index:");
	Serial.print(currentCommandIndex, DEC);
	Serial.print(" of ");
	Serial.println(this->maxArgumentIndex(), DEC);

	if (isComplete()) {
		Serial.println(" .. complete .. ");
		Serial.println();
		available = true;
	}
}

char* CommandClass::execute()
{
	disposed = true;
	Serial.println("======= print command argument ======");
	if (commandLength == 0) {
		Serial.println("No Args");
		return "No Args";
	}

	char* ch = printNumbers(commandArgument, commandLength);
	Serial.println();
	for (int i = 0; i < commandLength; i++)
	{
		Serial.print(commandArgument[i], DEC);
		Serial.print(" ");
	}
	Serial.println();
	return ( ch );
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
	return !this->isDisposed() && this->available && this->isComplete();
}

bool CommandClass::isDisposed()
{
	return this->disposed;
}

bool CommandClass::isComplete()
{
	return this->currentCommandIndex == this->maxArgumentIndex();
}



