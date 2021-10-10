// 
// 
// 

#include "CommandExecutor.h"

char* printCharacters(int inputs[], int size)
{
	char* string = "";
	for (int i = 0; i < size; i++)
	{
		char input = (char) inputs[i];
		char ch[] = { input };
		string = concatenate(string, ch);
	}
	return string;
}

void updateBlink(long delta, long* lastUpdated, int* lastStatus)
{
	long now = millis();
	long _lastUpdated = *lastUpdated;
	long _lastStatus = *lastStatus;
	if (now - _lastUpdated < delta) {
		return;
	}
	
	int mode = _lastStatus == 0 ? HIGH : LOW;
	digitalWrite(LED_PIN, mode);
	
	*lastUpdated = now;
	*lastStatus = _lastStatus == 1 ? 0 : 1;
}

char* executeCommand(CmdMode mode, int arguments[], int size)
{
	//Serial.println("EXEC COMMAND");
	switch (mode)
	{
	case NONE:
		return "No result";
	case PRINT_CHAR:
		return "Print char";
	case PRINT_NUMBER:
		return "Print number";
	case LED_ON:
		digitalWrite(LED_PIN, HIGH);
		return "OK: led ON";
	case LED_OFF:
		digitalWrite(LED_PIN, LOW);
		return "OK: led OFF";
	case LED_BLINK:
		return "OK: led BLINK";
	case STOP_COMMAND:
		int cmdModeToStop = arguments[0];
		stopByCommandMode(static_cast<CmdMode>(cmdModeToStop));
		return "OK: Stop command";
	default:
		return "INVALID COMMAND";
	}
}

bool updateCommand(
	CmdMode mode, 
	long *lastUpdated, 
	int *lastStatus, 
	int arguments[], 
	int size)
{
	bool continueCommand = true;
	switch (mode)
	{
		case LED_BLINK:
			updateBlink(arguments[0], lastUpdated, lastStatus);
			break;
		case LED_OFF:
		case LED_ON:
		case STOP_COMMAND:
		default:
			continueCommand = false;
			break;
	}

	return continueCommand;
}

int concat(int a, int b)
{

	char s1[20];
	char s2[20];

	// Convert both the integers to string
	sprintf(s1, "%d", a);
	sprintf(s2, "%d", b);

	// Concatenate both strings
	strcat(s1, s2);

	// Convert the concatenated string
	// to integer
	int c = atoi(s1);

	// return the formed integer
	return c;
}

char* printNumbers(int inputs[], int size)
{
	char* string = "";
	for (int i = 0; i < size; i++)
	{
		char input = inputs[i] + '0';
		char ch[] = { input };
		string = concatenate(string, ch);
	}
	return string;
}

