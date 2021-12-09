//
//
//

#include "CommandExecutor.h"

DCMotor* motors[5];
ServoExtended* servos[5];
//Servo* motors[5];
int motorCount = 0;
int servoCount = 0;

ServoExtended* getServo(int pin)
{
	int length = (sizeof(servos) / sizeof(*servos));
	if (servoCount >= length - 1)
	{
		return nullptr;
	}
	for (int i = 0; i < length; i++)
	{
		ServoExtended* motor = servos[i];
		if (motor != nullptr && motor->pin == pin)
		{
			return servos[i];
		}
		else
		{
			servos[servoCount] = new ServoExtended(pin);
			servoCount++;
			return servos[servoCount];
		}
	}
	
}

DCMotor *getMotor(int pin, int in1, int in2)
{
	int motorLength = (sizeof(motors) / sizeof(*motors));
	if (motorCount >= motorLength - 1)
	{
		return nullptr;
	}
	for (int i = 0; i < motorLength; i++)
	{
		DCMotor* motor = motors[i];
		if (motor != nullptr && motor->envPin == pin)
		{
			return motors[i];
		}
		else
		{
			motors[motorCount] = new DCMotor(in1, in2, pin);
			motorCount++;
			return motors[motorCount];
		}
	}
	
}

void updateBlink(
	const int ledPin,
	const long intervalMs,
	const long now,
	const long remainingDuration,
	long *lastUpdated,
	int *lastStatus)
{
	if (remainingDuration < 0)
	{
		digitalWrite(ledPin, LOW);
	}
	long _lastStatus = *lastStatus;

	if ((now - *lastUpdated) < intervalMs)
	{
		return;
	}

	int mode = _lastStatus == 0 ? HIGH : LOW;
	digitalWrite(ledPin, mode);

	*lastUpdated = now;
	*lastStatus = _lastStatus == 1 ? 0 : 1;
}

int executeCommand(CommandPayload *cmd)
{
	CmdMode mode = cmd->cmdName;
	if (mode == NONE)
	{
		return RESPONSE_OK;
	}
	if (mode == LED_ON)
	{
		digitalWrite(cmd->hardwarePin, HIGH);
		return RESPONSE_OK;
	}
	if (mode == LED_OFF)
	{
		digitalWrite(cmd->hardwarePin, LOW);
		return RESPONSE_OK;
	}
	if (mode == LED_BLINK)
	{
		return RESPONSE_OK;
	}
	if (mode == MOVE_SERVO)
	{
		ServoExtended *s = getServo(cmd->hardwarePin);
		if (nullptr == s)
		{
			return RESPONSE_FAILED;
		}
		s->write(cmd->angle);
		return RESPONSE_OK;
	}
	if (mode == READ_SERVO)
	{
		ServoExtended*s = getServo(cmd->hardwarePin);
		if (nullptr == s)
		{
			return RESPONSE_FAILED;
		}
		int angle = s->read();
		return angle;
	}
	if (mode == MOVE_MOTOR)
	{
		DCMotor *m = getMotor(cmd->hardwarePin, cmd->input1Pin, cmd->input2Pin);
		if (nullptr == m)
		{
			return RESPONSE_FAILED;
		}
		m->turnOn(1);
		m->write(cmd->speed);
		return RESPONSE_OK;
	}

	if (mode == STOP_MOTOR)
	{
		DCMotor *m = getMotor(cmd->hardwarePin, cmd->input1Pin, cmd->input2Pin);
		if (nullptr == m)
		{
			return RESPONSE_FAILED;
		}
		m->turnOff();
		return RESPONSE_OK;
	}

	return RESPONSE_INVALID_CMD;
}

bool updateCommand(CommandPayload *cmd)
{
	bool continueCommand = true;
	long now = millis();

	long remainingDuration = cmd->durationMs == 0 ? 1 : cmd->durationMs - (now - cmd->createdAt);
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
		if (remainingDuration < 0)
		{
			digitalWrite(cmd->hardwarePin, LOW);
		}
		//digitalWrite(arguments[0], HIGH);
		break;
	case STOP_COMMAND:
	default:
		continueCommand = false;
		break;
	}
	if (remainingDuration < 0)
	{
		continueCommand = false;
	}
	return continueCommand;
}
