// 
// 
// 

#include "CommandExecutor.h"
Servo* servoA = nullptr;
Servo* servoB = nullptr;
Servo* servoC = nullptr;

DCMotor* motorA = nullptr;
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
	case SERVO_C_PIN:
		
		if (servoC == nullptr)
		{
			servoC = new Servo();
			servoC->attach(pin);
		}
		return servoC;
	default:
		break;
		
	}
	return nullptr;
}

DCMotor* getMotor(int pin, int in1, int in2)
{

	switch (pin)
	{
	case MOTOR_A_PIN:

		if (motorA == nullptr)
		{
			motorA = new DCMotor(in1, in2, pin);
			motorA->begin();
		}
		return motorA;
	
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

int executeCommand(CommandPayload* cmd)
{
	CmdMode mode = cmd->cmdName;
	if (mode == NONE) {
		return RESPONSE_OK;
	}
	if (mode == LED_ON) {
		digitalWrite(cmd->hardwarePin, HIGH);
		return RESPONSE_OK;
	}
	if (mode == LED_OFF) {
		digitalWrite(cmd->hardwarePin, LOW);
		return RESPONSE_OK;
	}
	if (mode == LED_BLINK) {
		return RESPONSE_OK;
	}
	if (mode == MOVE_SERVO)
	{
		Servo*  s = getServo(cmd->hardwarePin);
		if (nullptr == s)
		{
			return RESPONSE_FAILED;
		}
		s->write(cmd->angle);
		return RESPONSE_OK;
	}
	if (mode == READ_SERVO)
	{
		Servo* s = getServo(cmd->hardwarePin);
		if (nullptr == s)
		{
			return RESPONSE_FAILED;
		}
		int angle = s->read();
		return angle;
	}
	if (mode == MOVE_MOTOR)
	{
		DCMotor* m = getMotor(cmd->hardwarePin, cmd->input1Pin, cmd->input2Pin);
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
    DCMotor* m = getMotor(cmd->hardwarePin, cmd->input1Pin, cmd->input2Pin);
    if (nullptr == m)
    {
      return RESPONSE_FAILED;
    }
    m->turnOff();
    return RESPONSE_OK;
  }

	return RESPONSE_INVALID_CMD;
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
