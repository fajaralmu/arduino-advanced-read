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
	cmd->setSize(3);
	cmd->appendCommandArgument(LED_PIN); // hardware pin
	cmd->appendCommandArgument(10); // duration sec
	cmd->appendCommandArgument(1); // interval sec
	return cmd;
}

void addDefaultCommands() { activeCommand = sampleBlinkCommand(); }

void reset()
{
	currentArgumentIndex = 0;
	activeCommand = nullptr;
}

void preProccess() { reset(); }

void addCommand(int mode)
{
	serialWrite("[NEW COMMAND] >> ");
	// delete current acvite command
	delete activeCommand;

	// create new command
	activeCommand = new CommandClass(mode);

	serialWrite("Selected mode:");
	serialWrite(mode);
	serialWriteLn(" ID ", activeCommand->getId());
}

void setCommandLength(int length)
{
	if (nullptr == activeCommand)
	{
		return;
	}
	activeCommand->setSize(length);

	serialWriteLn("Command length",activeCommand->getSize());
}

void appendCommand(int commandItem)
{
	if (nullptr == activeCommand)
	{
		return;
	}
	activeCommand->appendCommandArgument(commandItem);

	serialWrite	(">> arg:");
	serialWrite	(commandItem);
	serialWrite	(" index ");
	serialWrite	(activeCommand->getCurrentCommandIndex());
	serialWrite	(" of ");
	serialWriteLn	(activeCommand->getMaxCommandIndex());

	if (activeCommand->isComplete())
	{
		serialWriteLn("Arguments Complete. Will execute");
	}
}

void incrementCurrentIndex() { currentArgumentIndex++; }

void processInput(int input)
{
	serialWrite("==> ");
	serialWrite(input);
	serialWriteLn(" POS ", currentArgumentIndex );

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
			serialWriteLn("Invalid length");
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
	//serialWriteLn("Check current command");
	if (activeCommand != nullptr && activeCommand->isComplete()) {
		serialWriteLn("---------------------------------");
		serialWriteLn("Command is complete Please enter another command");
		serialWriteLn();

		currentArgumentIndex = 0;
	}
}

void applyCommands()
{
	if (activeCommand == nullptr) return;
	if (activeCommand->isExecutable())
	{
		serialWriteLn("<!>START Execute Cmd - ", activeCommand->getId());

		char* result = activeCommand->execute();

		serialWriteLn("[RESULT]", result);
		serialWriteResponse( activeCommand->getCommandName(), result );
	}
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
