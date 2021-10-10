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

int currentArgumentIndex = 0;
int commandIndex = 0;

Commandv2* commands[COMMAND_MAX_COUNT] = { nullptr };
Commandv2* currentCommand = nullptr;

void reset()
{
	currentArgumentIndex = 0;
	//currentCommand = nullptr;
	const int size = commandIndex;
	for (int i = 0; i < size; i++)
	{
		Commandv2* cmd = commands[i];
		if (Cmd_isDisposed(cmd))
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
	Commandv2* command;
	command = new(Commandv2);
	Cmd_ctor(command, mode);
	currentCommand = command;
	commands[commandIndex] = currentCommand;

	commandIndex++;
	Serial.print("Selected mode:");
	Serial.print(mode, DEC);
	Serial.print(" ID:");
	Serial.println(Cmd_getId(currentCommand));

	Serial.println("Please input command length:");
}

void setCommandLength(int length)
{
	Cmd_setSize(currentCommand, length);

	Serial.print("Command length:");
	Serial.println(Cmd_getSize(currentCommand), DEC);
}

void appendCommand(int commandItem)
{
	Cmd_appendCommandArgument(currentCommand, commandItem);
	int currentIndex = Cmd_getCurrentCommandIndex(currentCommand);
	int cmdLength = Cmd_getMaxArgumentIndex(currentCommand);
	Serial.print(">> arg:");
	Serial.print(commandItem);
	Serial.print(" index ");
	Serial.print(currentIndex);
	Serial.print(" of ");
	Serial.println(cmdLength);

	if (Cmd_isComplete(currentCommand))
	{
		int match = currentCommand == commands[commandIndex - 1] ? 1 : 0;
		Serial.println("Arguments Complete. Will execute");
		Serial.print("Current command match:");
		Serial.println(match, DEC);

	}
}

void incrementCurrentIndex() { currentArgumentIndex++; }

void processInput(int input)
{
	Serial.print("Received input:");
	Serial.println(input, DEC);
	Serial.print("currentArgumentIndex:");
	Serial.println(currentArgumentIndex);
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
	if (Cmd_isComplete(currentCommand) ==  false)
	{
		appendCommand(input);
	}
}

void checkCurrentCommand()
{
	//Serial.println("Check current command");
	if (currentCommand != nullptr && Cmd_isComplete(currentCommand)) {

		Serial.println("Command is complete Please enter another command");
		currentArgumentIndex = 0;
	}
}

void applyCommands()
{
	const int size = commandIndex;
	//Serial.println(" == APPLYING COMMANDS == ");
	for (int i = 0; i < size; i++)
	{
		Commandv2* cmd = commands[i];
		if (cmd != nullptr && Cmd_isExecutable(cmd))
		{
			Serial.print("START Execute Cmd - ");
			Serial.println(Cmd_getId(cmd));

			char* result = Cmd_execute(cmd);

			Serial.print("Result: ");
			Serial.println(result);
		}
	}
	/*Serial.print("total Cmd");
	Serial.println(size, DEC);*/

}
