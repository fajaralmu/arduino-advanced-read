// 
// 
// 

#include "SerialWriter.h"

bool enablePrint = true;

void serialWrite(char* value=nullptr)
{
	if (enablePrint)
	{
		Serial.print(value);
	}
}

void serialWriteLn(char* value = nullptr)
{
	if (value == nullptr)
	{
		if (enablePrint)
		{
			Serial.println();
		}
		return;
	}
	if (enablePrint)
	{
		Serial.println(value);
	}
}

void serialWrite(int value)
{
	if (enablePrint)
	{
		Serial.print(value);
	}
}

void serialWriteLn(int value)
{
	if (enablePrint)
	{
		Serial.println(value);
	}
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

void serialWriteResponse( CmdMode mode, int response )
{
	Serial.println(START_OF_HEADING);
	Serial.println(mode);
	Serial.println(START_OF_TEXT);
	Serial.println(response, DEC);
	Serial.println(END_OF_TEXT);
	Serial.println(END_OF_TRANSMISSION);
}
void serialWriteResponse( CmdMode mode, char* response )
{
	Serial.println(START_OF_HEADING);
	Serial.println(mode);
	Serial.println(START_OF_TEXT);
	Serial.println(response);
	Serial.println(END_OF_TEXT);
	Serial.println(END_OF_TRANSMISSION);
}
