// 
// 
// 

#include "Process.h"
#include <Arduino.h>
#define BEGIN_KEY			13
#define MODE_PRINT_NUMBER	1
#define MODE_PRINT_CHATS	2
#define INDEX_MODE			1
#define INDEX_SIZE			2
#define COMMAND_MAX_LENGTH	512

int commands[COMMAND_MAX_LENGTH] = { 0 };

unsigned int currentMode;
int currentIndex = 0;
int currentCommandCount = 0;

void reset()
{
	Serial.println("Reset Commands");
	currentIndex = 0;
	currentCommandCount = 0;
	memset(commands, 0, COMMAND_MAX_LENGTH);
}

void applyCommands()
{
	Serial.println("Applying command");
	Serial.println("Command values:");
	for (int i = 0; i < currentCommandCount; i++)
	{
		Serial.print(commands[i], DEC);
	}
	Serial.println();
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

void processInput(int input)
{
	//Serial.println(input);
	if (currentIndex == 0)
	{
		currentMode = input;
		currentIndex++;
		Serial.print("Selected mode:");
		Serial.println(input, DEC);

		Serial.println("Please input command length:");
		return;
	}

	if (currentIndex == 1)
	{
		if (input > COMMAND_MAX_LENGTH)
		{
			Serial.println("Invalid length");
			reset();
			return;
		}
		currentCommandCount = input;
		Serial.print("Command length:");
		Serial.println(input, DEC);
		currentIndex++;
		
		return;
	}

	if (currentIndex > 1)
	{
		int toAppendIndex = currentIndex - 2;
		commands[toAppendIndex] = input;
		currentIndex++;
		/*Serial.print("current index: ");
		Serial.println(currentIndex, DEC);*/
	}

	if (currentCommandCount == (currentIndex - 2))
	{
		applyCommands();
		reset();
	}


}


