// 
// 
// 

#include "SerialWriter.h"

void serialWrite(char* value=nullptr)
{
	Serial.print(value);
}

void serialWriteLn(char* value = nullptr)
{
	if (value == nullptr)
	{
		Serial.println();
		return;
	}
	Serial.println(value);
}

void serialWrite(int value)
{
	Serial.print(value);
}

void serialWriteLn(int value)
{
	Serial.println(value);
}

void serialWriteLn(char* label, int value)
{
	serialWrite(label);
	serialWrite(":");
	serialWriteLn(value);
}

void serialWriteLn(char* label, char* value)
{
	serialWrite(label);
	serialWrite(":");
	serialWriteLn(value);
}

void serialWriteResponse( CmdMode mode, char* response )
{
	serialWriteLn(START_OF_HEADING);
	serialWriteLn(mode);
	serialWriteLn(START_OF_TEXT);
	serialWriteLn(response);
	serialWriteLn(END_OF_TEXT);
	serialWriteLn(END_OF_TRANSMISSION);
}
