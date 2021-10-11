// 
// 
// 

#include "CommandExecutor.h"


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

char* executeCommand(CmdMode mode, int arguments[], int size)
{
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
		updateBlink(ledPin, intervalSec*1000, now, remainingDuration, lastUpdated, lastStatus);
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
	if (remainingDuration < 0) {
		continueCommand = false;
	}
	return continueCommand;
}

