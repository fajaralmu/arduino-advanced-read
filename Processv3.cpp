//#include "Process.h"
//#include "CommandName.h"
//#include <Arduino.h>
//
//#define INDEX_INPUT_MODE	0
//#define INDEX_INPUT_SIZE	1
//#define COMMAND_MAX_LENGTH	255
//
//using namespace std;
//
//int currentArgumentIndex = 0;
//int commandIndex = 0;
//int _defaultCommandAdded = 0;
//
//Commandv2* currentCommand = nullptr;
//
//void updateCommnadCountInRepo()
//{
//	setCommandCount(commandIndex);
//}
//
//Commandv2* sampleBlinkCommand()
//{
//	Commandv2* cmd = new(Commandv2);
//	Cmd_ctor2(cmd, LED_BLINK);
//	cmd->commandArgument[0] = 1000;
//	cmd->commandLength = 1;
//	cmd->currentCommandIndex = 0;
//	cmd->available = 1;
//	return cmd;
//}
//
//void putCommandToRepo(Commandv2* command)
//{
//	putCommand(command, commandIndex);
//	commandIndex = commandIndex + 1;
//	updateCommnadCountInRepo();
//}
//void reset()
//{
//	currentArgumentIndex = 0;
//	const int size = commandIndex;
//	for (int i = 0; i < size; i++)
//	{
//		Commandv2* cmd = getCommand(i);
//		if (Cmd_isDisposed(cmd))
//		{
//			putCommand(nullptr, i);
//			delete cmd;
//		}
//	}
//}
//
//void preProccess() { reset(); }
//
//void addCommand(int mode)
//{
//	Serial.println("Add cmd");
//	Commandv2* command;
//	command = new(Commandv2);
//	Cmd_ctor(command, mode);
//	currentCommand = command;
//	putCommandToRepo(command);
//
//	Serial.print("Selected mode:");
//	Serial.print(mode, DEC);
//	Serial.print(" ID:");
//	Serial.println(Cmd_getId(currentCommand));
//
//	Serial.println("Please input command length:");
//}
//
//void setCommandLength(int length)
//{
//	int result = Cmd_setSize(currentCommand, length);
//
//	Serial.print("Set length:");
//	Serial.println(result, DEC);
//	Serial.print("Command length:");
//	Serial.println((currentCommand->commandLength), DEC);
//
//	Serial.println(Cmd_getSize(currentCommand), DEC);
//}
//
//void appendCommand(int commandItem)
//{
//	Cmd_appendCommandArgument(currentCommand, commandItem);
//	int currentIndex = Cmd_getCurrentCommandIndex(currentCommand);
//	int cmdLength = Cmd_getMaxArgumentIndex(currentCommand);
//	Serial.print(">> arg:");
//	Serial.print(commandItem);
//	Serial.print(" index ");
//	Serial.print(currentIndex);
//	Serial.print(" of ");
//	Serial.println(cmdLength);
//
//	if (Cmd_isComplete(currentCommand))
//	{
//		int match = currentCommand == getCommand(commandIndex - 1) ? 1 : 0;
//		Serial.println("Arguments Complete. Will execute");
//		Serial.print("Current command match:");
//		Serial.println(match, DEC);
//
//	}
//}
//
//void incrementCurrentIndex() { currentArgumentIndex++; }
//
//void processInput(int input)
//{
//	Serial.print("==> ");
//	Serial.print(input, DEC);
//	Serial.print(" POS :");
//	Serial.print(currentArgumentIndex, DEC);
//	Serial.print(" total cmd: ");
//	Serial.println(commandIndex);
//	if (currentArgumentIndex == INDEX_INPUT_MODE)
//	{
//		addCommand(input);
//		incrementCurrentIndex();
//		return;
//	}
//	//space = 32
//	if (currentArgumentIndex == INDEX_INPUT_SIZE)
//	{
//		if (input > COMMAND_MAX_LENGTH)
//		{
//			Serial.println("Invalid length");
//			reset();
//			return;
//		}
//		setCommandLength(input);
//		incrementCurrentIndex();
//		return;
//	}
//	if (Cmd_isComplete(currentCommand) == false)
//	{
//		appendCommand(input);
//	}
//}
//
//void checkCurrentCommand()
//{
//	//Serial.println("Check current command");
//	if (currentCommand != nullptr && Cmd_isComplete(currentCommand)) {
//		Serial.println("---------------------------------");
//		Serial.println("Command is complete Please enter another command");
//		currentArgumentIndex = 0;
//	}
//}
//
//char* executeByCmdExecutor(Commandv2* me)
//{
//	return executeCommand(me->commandName, me->commandArgument, Cmd_getSize(me));
//}
//
//void applyCommands()
//{
//	const int size = commandIndex;
//
//	for (int i = 0; i < size; i++)
//	{
//		Commandv2* cmd = getCommand(i);
//		if (cmd != nullptr && Cmd_isExecutable(cmd))
//		{
//			Serial.print("<!>START Execute Cmd - ");
//			Serial.println(Cmd_getId(cmd));
//
//			Cmd_execute(cmd);
//			char* result = executeByCmdExecutor(cmd);
//
//			Serial.print("[RESULT]: ");
//			Serial.println(result);
//		}
//	}
//	/*Serial.print("total Cmd");
//	Serial.println(size, DEC);*/
//
//}
//
//void updateByCmdExecutor(Commandv2* me)
//{
//	bool active = updateCommand(me->commandName, &me->lastUpdated, &me->lastStatus, me->commandArgument, Cmd_getSize(me));
//	if (!active)
//	{
//		Cmd_dispose(me);
//	}
//}
//
//void addDefaultCommands()
//{
//	putCommandToRepo(sampleBlinkCommand());
//}
//
//void updateCommands()
//{
//	if (0 == _defaultCommandAdded)
//	{
//		addDefaultCommands();
//		_defaultCommandAdded = 1;
//	}
//
//	const int size = commandIndex;
//	for (int i = 0; i < size; i++)
//	{
//		Commandv2* cmd = getCommand(i);
//		if (cmd == nullptr || 0 == Cmd_isStarted(cmd) || 1 == Cmd_isDisposed(cmd))
//			continue;
//		Cmd_update(cmd);
//		updateByCmdExecutor(cmd);
//
//	}
//	/*Serial.print("total Cmd");
//	Serial.println(size, DEC);*/
//	updateCommnadCountInRepo();
//
//}
