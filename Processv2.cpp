#include "Process.h"
#include <Arduino.h>

#define INDEX_INPUT_MODE	0
#define INDEX_INPUT_SIZE	1

using namespace std;

int currentArgumentIndex = 0;
int _defaultCommandAdded = 0;

CommandClass* currentCommand = nullptr;

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
	currentCommand = nullptr;
}

void preProccess() { reset(); }

void addCommand(int mode)
{
	Serial.println("Add cmd:");
	delete currentCommand;
	CommandClass* command;
	command = new CommandClass(mode);
	currentCommand = command;
	Serial.print("Selected mode:");
	Serial.print(mode, DEC);
	Serial.print(" ID:");
	Serial.println(command->getId());

	Serial.println("Please input command length:");
}

void setCommandLength(int length)
{
	if (nullptr == currentCommand) return;
	currentCommand->setSize(length);

	Serial.print("Command length:");
	Serial.println(currentCommand->getSize(), DEC);
}

void appendCommand(int commandItem)
{
	if (nullptr == currentCommand) return;
	currentCommand->appendCommandArgument(commandItem);
	int currentIndex = currentCommand->getCurrentCommandIndex();
	int cmdLength = currentCommand->getMaxCommandIndex();
	Serial.print(">> arg:");
	Serial.print(commandItem);
	Serial.print(" index ");
	Serial.print(currentIndex);
	Serial.print(" of ");
	Serial.println(cmdLength);

	if (currentCommand->isComplete())
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
	if (currentCommand->isComplete() == false)
	{
		appendCommand(input);
	}
}

void checkCurrentCommand()
{
	//Serial.println("Check current command");
	if (currentCommand != nullptr && currentCommand->isComplete()) {
		int currIndx = currentCommand->getCurrentCommandIndex();
		int maxIndx = currentCommand->getMaxCommandIndex();
		Serial.println("---------------------------------");
		Serial.println("Command is complete Please enter another command");
		Serial.print(currIndx, DEC);
		Serial.print(" of ");
		Serial.println(maxIndx, DEC);

		currentArgumentIndex = 0;
	}
}

char* executeByCmdExecutor(CommandClass* me)
{
	return executeCommand(
		me->getCommandName(),
		me->getArguments(),
		me->getSize());
}

void applyCommands()
{
	if (currentCommand == nullptr) return;
	if (currentCommand->isExecutable())
	{
		Serial.print("<!>START Execute Cmd - ");
		Serial.println(currentCommand->getId());

		currentCommand->execute();
		char* result = executeByCmdExecutor(currentCommand);

		Serial.print("[RESULT]: ");
		Serial.println(result);
	}
}

void updateByCmdExecutor(CommandClass* me)
{
	bool active = updateCommand(
		me->getCommandName(),
		&me->lastUpdated,
		&me->lastStatus,
		me->getArguments(),
		me->getSize());
	if (!active)
	{
		me->dispose();
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
	CommandClass* cmd = currentCommand;
	if (cmd == nullptr || 0 == cmd->isStarted() || 1 == cmd->isDisposed())
		return;
	cmd->update();
	updateByCmdExecutor(cmd);

}
