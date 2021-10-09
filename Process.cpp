// 
// 
// 

#include "Process.h"
#include <Arduino.h>
#define BEGIN_KEY			13
#define MODE_PRINT_NUMBER	1
#define MODE_PRINT_CHAR		2
#define INDEX_INPUT_MODE	0
#define INDEX_INPUT_SIZE	1
#define COMMAND_MAX_LENGTH	512

int commands[COMMAND_MAX_LENGTH] = { 0 };

unsigned int currentMode;
int currentIndex = 0;
int commandLength = 0;

void reset()
{
	Serial.println("Reset Commands");
	currentIndex = 0;
	commandLength = 0;
	memset(commands, 0, COMMAND_MAX_LENGTH);
}

char* commandString()
{
	switch (currentMode)
	{
		case MODE_PRINT_CHAR: return "Print Character";
		case MODE_PRINT_NUMBER: return "Print Number";
		default: return "Invalid mode";
	}
}

void applyCommands()
{
	Serial.println(concatenate("Applying command:", commandString()));
	if (commandLength == 0) {
		Serial.println("NO INPUT");
		reset();
		return;
	}
	char* result;
	switch (currentMode)
	{
		case MODE_PRINT_CHAR:
			result = printCharacters(commands, commandLength);
			break;
		case MODE_PRINT_NUMBER:
			result = printNumbers(commands, commandLength);
			break;
		default:
			break;
	}
	
	Serial.println("Result:");
	Serial.println(result);
	Serial.println();
}

void preProccess()
{
	Serial.println("===================================================");
	Serial.println("                   Welcome                         ");
	Serial.println("===================================================");
	Serial.println("Please input command mode:");
	reset();
}

void setSelectedMode(int mode)
{
	currentMode = mode;

	Serial.print("Selected mode:");
	Serial.println(mode, DEC);
	Serial.println("Please input command length:");
}

void setCommandLength(int length)
{
	commandLength = length;

	Serial.print("Command length:");
	Serial.println(length, DEC);
}

void appendCommand(int commandItem)
{
	int toAppendIndex = currentIndex - 2;
	commands[toAppendIndex] = commandItem;
}

void incrementCurrentIndex() { currentIndex++; }

void processInput(int input)
{
	//Serial.println(input);
	if (currentIndex == INDEX_INPUT_MODE)
	{
		setSelectedMode(input);
		incrementCurrentIndex();
		return;
	}

	if (currentIndex == INDEX_INPUT_SIZE)
	{
		if (input > COMMAND_MAX_LENGTH)
		{
			Serial.println("Invalid length");
			reset();
			return;
		}
		setCommandLength(input);
		if (commandLength == 0) {
			applyCommands();
			return;
		}
		incrementCurrentIndex();
		return;
	}

	if (currentIndex > INDEX_INPUT_SIZE)
	{
		appendCommand(input);
		incrementCurrentIndex();
	}

	if (commandLength == (currentIndex - 2))
	{
		applyCommands();
		reset();
	}


}


