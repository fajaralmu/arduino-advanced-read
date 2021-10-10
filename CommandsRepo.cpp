// 
// 
// 

#include "CommandsRepo.h"


int commandCount = 0;

Commandv2* commands[COMMAND_MAX_COUNT] = { nullptr };

Commandv2** getCommands()
{
	return commands;
}



int getCommandCount() {
	return commandCount;
}

Commandv2* getCommand(int index)
{
	return commands[index];
}

void putCommand(Commandv2* cmd, int index)
{
	commands[index] = cmd;
}

void resetCommands()
{
	//
}

void stopByCommandMode(CmdMode mode)
{
	for (int i = 0; i < getCommandCount(); i++)
	{
		Commandv2* cmd = getCommand(i);
		if (cmd == nullptr) continue;
		if (cmd->commandName == mode)
		{
			Cmd_dispose(cmd);
		}
	}
}

void setCommandCount(int count)
{
	commandCount = count;
}
