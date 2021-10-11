// 
// 
// 

#include "CommandExecutor.h"

/// <summary>
/// 
/// </summary>
/// <param name="delta">second</param>
/// <param name="lastUpdated"></param>
/// <param name="lastStatus"></param>
void updateBlink(int ledPin, long deltaAsSecond, long* lastUpdated, int* lastStatus)
{
	long now = millis();
	long _lastUpdated = *lastUpdated;
	long _lastStatus = *lastStatus;
	if (now - _lastUpdated < deltaAsSecond * 1000) {
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
	long* lastUpdated,
	int* lastStatus,
	int arguments[],
	int size)
{
	bool continueCommand = true;
	switch (mode)
	{
	case LED_BLINK:
		updateBlink(arguments[0], arguments[1], lastUpdated, lastStatus);
		break;
	case LED_OFF:
	//	digitalWrite(arguments[0], LOW);
		break;
	case LED_ON:
		//digitalWrite(arguments[0], HIGH);
		break;
	case STOP_COMMAND:
	default:
		continueCommand = false;
		break;
	}

	return continueCommand;
}

