// 
// 
// 

#include "CommandExecutor.h"
Servo* servoA = nullptr;
Servo* servoB = nullptr;
//Servo* motors[5];

Servo*  getServo(int pin)
{
	
	switch (pin)
	{
	case SERVO_A_PIN:
		
		if (servoA == nullptr)
		{
			servoA = new Servo();
			servoA->attach(pin);
		}
		return servoA;
	case SERVO_B_PIN:
		
		if (servoB == nullptr)
		{
			servoB = new Servo();
			servoB->attach(pin);
		}
		return servoB;
	default:
		break;
		
	}
	return nullptr;
}

void updateBlink(
	const int ledPin, 
	const long intervalMs, 
	const long now,
	const long remainingDuration,
	long* lastUpdated, 
	int* lastStatus)
{
	if (remainingDuration < 0) {
		digitalWrite(ledPin, LOW);
	}
	long _lastStatus = *lastStatus;

	if ((now - *lastUpdated) < intervalMs) {
		return;
	}

	int mode = _lastStatus == 0 ? HIGH : LOW;
	digitalWrite(ledPin, mode);

	*lastUpdated = now;
	*lastStatus = _lastStatus == 1 ? 0 : 1;
}

char* executeCommand(CommandPayload* cmd)
{
	CmdMode mode = cmd->cmdName;
	if (mode == NONE) {
		return "No Operation";
	}
	if (mode == LED_ON) {
		digitalWrite(cmd->hardwarePin, HIGH);
		return "OK: LED on";
	}
	if (mode == LED_OFF) {
		digitalWrite(cmd->hardwarePin, LOW);
		return "OK: LED off";
	}
	if (mode == LED_BLINK) {
		return "OK: LED blink";
	}
	if (mode == MOVE_SERVO)
	{
		Servo*  s = getServo(cmd->hardwarePin);
		if (nullptr == s)
		{
			return "[Error] Servo not found";
		}
		s->write(cmd->angle);
		return "OK :Move servo";
	}

	return "Invalid Command";
}

bool updateCommand(CommandPayload* cmd)
{
	bool continueCommand = true;
	long now = millis();

	long remainingDuration = cmd->durationMs == 0 ? 1 : cmd->durationMs - ( now - cmd->createdAt);
	switch (cmd->cmdName)
	{
	case LED_BLINK:
		updateBlink(
			cmd->hardwarePin, 
			cmd->intervalMs, now, 
			remainingDuration, 
			cmd->lastUpdated,
			cmd->lastStatus);
		break;
	case LED_OFF:
	//	digitalWrite(arguments[0], LOW);
		break;
	case LED_ON:
		if (remainingDuration < 0) {
			digitalWrite(cmd->hardwarePin, LOW);
		}
		//digitalWrite(arguments[0], HIGH);
		break;
	case STOP_COMMAND:
	default:
		continueCommand = false;
		break;
	}
	if (remainingDuration < 0) {
		continueCommand = false;
	}
	return continueCommand;
}

