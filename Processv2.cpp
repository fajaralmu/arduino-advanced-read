#include "Process.h"
#include "CommandName.h"
#include <Arduino.h>

#define MODE_PRINT_NUMBER	1
#define MODE_PRINT_CHAR		2
#define INDEX_INPUT_MODE	0
#define INDEX_INPUT_SIZE	1
#define COMMAND_MAX_LENGTH	255
#define COMMAND_MAX_COUNT   50

using namespace std;

int currentArgumentIndex	= 0;
int commandIndex			= 0;

CommandClass* commands[COMMAND_MAX_COUNT] = { nullptr };
CommandClass* currentCommand = nullptr;

void reset()
{
	currentArgumentIndex = 0;
	//currentCommand = nullptr;
	const int size = commandIndex;
	for (int i = 0; i < size; i++)
	{
		CommandClass* cmd = commands[i];
		if (cmd->isDisposed())
		{
			commands[i] = nullptr;
			delete cmd;
		}
	}
}
void preProccess()
{
	Serial.println("===================================================");
	Serial.println("                   Welcome                         ");
	Serial.println("===================================================");
	Serial.println("Please input command mode:");
	reset();
}

void addCommand(int mode)
{
	CommandClass* command;
	command = &CommandClass(mode);
	currentCommand = command;
	commands[commandIndex] = currentCommand;

	commandIndex++;
	Serial.print("Selected mode:");
	Serial.print(mode, DEC);
	Serial.print(" ID:");
	Serial.println(currentCommand->getId(), DEC);

	Serial.println("Please input command length:");
}

void setCommandLength(int length)
{
	currentCommand->setSize(length);

	Serial.print("Command length:");
	Serial.println(currentCommand->getSize(), DEC);
}

void appendCommand(int commandItem)
{
	currentCommand->appendCommandArgument(commandItem);
	int currentIndex = currentCommand->getCurrentCommandIndex();
	int commandLength = currentCommand->getSize();
	
	Serial.print("Command progress:");
	Serial.print(currentIndex, DEC);
	Serial.print(" of ");
	Serial.println(commandLength - 1, DEC);

	if (currentCommand->isComplete())
	{
		int match = currentCommand == commands[commandIndex-1] ? 1 : 0;
		Serial.println("Arguments Complete. Will execute");
		Serial.print("Current command match:");
		Serial.println(match, DEC);
	}
}

void incrementCurrentIndex() { currentArgumentIndex++; }

void processInput(int input)
{
	if (currentArgumentIndex == INDEX_INPUT_MODE)
	{
		addCommand(input);
		incrementCurrentIndex();
		return;
	}
	//space = 32
	if (currentArgumentIndex == INDEX_INPUT_SIZE)
	{
		if (input > COMMAND_MAX_LENGTH)
		{
			Serial.println("Invalid length");
			reset();
			return;
		}
		setCommandLength(input);
		incrementCurrentIndex();
		return;
	}
	if (currentCommand->isComplete()== false)
	{
		appendCommand(input);
	}

}

void checkCurrentCommand()
{
	if (currentCommand != nullptr && currentCommand->isExecutable()) {
		
		Serial.print("Command is complete Please enter another command");
		Serial.print(". cmd arg:");
		Serial.print(currentCommand->getCurrentCommandIndex(), DEC);
		Serial.print(" of ");
		Serial.println(currentCommand->getSize(), DEC);
		
		currentArgumentIndex = 0;
	}
}

void applyCommands()
{
	const int size = commandIndex;
	//Serial.println(" == APPLYING COMMANDS == ");
	for (int i = 0; i < size; i++)
	{
		CommandClass* cmd = commands[i];
		if (cmd != nullptr && cmd->isExecutable())
		{
			Serial.print("Execute Cmd ID:");
			Serial.print(commands[i]->getId(), DEC);

			char* result = commands[i]->execute();
		}
	}
	/*Serial.print("total Cmd");
	Serial.println(size, DEC);*/

}
