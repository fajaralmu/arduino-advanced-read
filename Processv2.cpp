#include "Process.h"
#include <Arduino.h>

#define INDEX_INPUT_MODE	0
#define INDEX_INPUT_SIZE	1

using namespace std;

int currentArgumentIndex = 0;
int _defaultCommandAdded = 0;

CommandClass* activeCommand = nullptr;

CommandClass* sampleBlinkCommand()
{
	CommandClass* cmd = new CommandClass(LED_BLINK);
	cmd->setSize(1);
	cmd->appendCommandArgument(1000);
	return cmd;
}

void reset()
{
	currentArgumentIndex = 0;
	activeCommand = nullptr;
}

void preProccess() { reset(); }

void addCommand(int mode)
{
	Serial.print("[NEW COMMAND] >> ");
	delete activeCommand;
	CommandClass* command;
	command = new CommandClass(mode);
	activeCommand = command;
	Serial.print("Selected mode:");
	Serial.print(mode, DEC);
	Serial.print(" ID:");
	Serial.println(command->getId());
}

void setCommandLength(int length)
{
	if (nullptr == activeCommand) return;
	activeCommand->setSize(length);

	Serial.print("Command length:");
	Serial.println(activeCommand->getSize(), DEC);
}

void appendCommand(int commandItem)
{
	if (nullptr == activeCommand) return;
	activeCommand->appendCommandArgument(commandItem);
	int currentIndex = activeCommand->getCurrentCommandIndex();
	int cmdLength = activeCommand->getMaxCommandIndex();
	Serial.print(">> arg:");
	Serial.print(commandItem);
	Serial.print(" index ");
	Serial.print(currentIndex);
	Serial.print(" of ");
	Serial.println(cmdLength);

	if (activeCommand->isComplete())
	{
		Serial.println("Arguments Complete. Will execute");
	}
}

void incrementCurrentIndex() { currentArgumentIndex++; }

void processInput(int input)
{
	Serial.print("==> ");
	Serial.print(input, DEC);
	Serial.print(" POS :");
	Serial.println(currentArgumentIndex, DEC);
	if (currentArgumentIndex == INDEX_INPUT_MODE)
	{
		addCommand(input);
		incrementCurrentIndex();
		return;
	}
	//space = 32
	if (currentArgumentIndex == INDEX_INPUT_SIZE)
	{
		if (input > CMD_MAX_LENGTH)
		{
			Serial.println("Invalid length");
			reset();
			return;
		}
		setCommandLength(input);
		incrementCurrentIndex();
		return;
	}
	if (activeCommand->isComplete() == false)
	{
		appendCommand(input);
	}
}

void checkCurrentCommand()
{
	//Serial.println("Check current command");
	if (activeCommand != nullptr && activeCommand->isComplete()) {
		Serial.println("---------------------------------");
		Serial.println("Command is complete Please enter another command");
		Serial.println();

		currentArgumentIndex = 0;
	}
}

void applyCommands()
{
	if (activeCommand == nullptr) return;
	if (activeCommand->isExecutable())
	{
		Serial.print("<!>START Execute Cmd - ");
		Serial.println(activeCommand->getId());

		char* result = activeCommand->execute();

		Serial.print("[RESULT]: ");
		Serial.println(result);
	}
}

void addDefaultCommands()
{
	//currentCommand = (sampleBlinkCommand());
}

void updateCommands()
{
	if (0 == _defaultCommandAdded)
	{
		addDefaultCommands();
		_defaultCommandAdded = 1;
	}
	CommandClass* cmd = activeCommand;
	if (cmd == nullptr || 0 == cmd->isStarted() || 1 == cmd->isDisposed())
		return;
	cmd->update();

}
