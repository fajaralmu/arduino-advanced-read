// 
// 
// 

#include "CommandExecutor.h"


void updateBlink(
	const int ledPin, 
	const long deltaAsSecond, 
	const long remainingDuration,
	const long lastUpdated, 
	int* lastStatus)
{
	if (remainingDuration < 0) {
		digitalWrite(ledPin, LOW);
	}
	long now = millis();
	long _lastStatus = *lastStatus;
	if (now - lastUpdated < deltaAsSecond * 1000) {
		return;
	}

	int mode = _lastStatus == 0 ? HIGH : LOW;
	digitalWrite(ledPin, mode);

	*lastStatus = _lastStatus == 1 ? 0 : 1;
}

char* executeCommand(CmdMode mode, int arguments[], int size)
{
	Serial.println("Exec Command:");
	Serial.println(mode, DEC);
	if (mode == NONE) {
		return "No Operation";
	}
	if (mode == LED_ON) {
		int ledPin = arguments[0];
		digitalWrite(ledPin, HIGH);
		return "OK: LED on";
	}
	if (mode == LED_OFF) {
		int ledPin = arguments[0];
		digitalWrite(ledPin, LOW);
		return "OK: LED off";
	}
	if (mode == LED_BLINK) {
		return "OK: LED blink";
	}

	return "Invalid Command";
}

bool updateCommand(
	CmdMode mode,
	long createdAt,
	long* lastUpdated,
	int* lastStatus,
	int arguments[],
	int size)
{
	bool continueCommand = true;
	long now = millis();

	int ledPin		= arguments[0];
	int intervalSec = arguments[1];
	int duration	= arguments[2];

	long remainingDuration = (duration*1000) - ( now - createdAt );
	switch (mode)
	{
	case LED_BLINK:
		updateBlink(arguments[0], arguments[1], remainingDuration, *lastUpdated, lastStatus);
		break;
	case LED_OFF:
	//	digitalWrite(arguments[0], LOW);
		break;
	case LED_ON:
		if (remainingDuration < 0) {
			digitalWrite(ledPin, LOW);
		}
		//digitalWrite(arguments[0], HIGH);
		break;
	case STOP_COMMAND:
	default:
		continueCommand = false;
		break;
	}

	*lastUpdated = now;
	return continueCommand;
}

