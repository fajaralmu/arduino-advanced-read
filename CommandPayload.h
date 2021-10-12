// CommandPayload.h

#ifndef _COMMANDPAYLOAD_h
#define _COMMANDPAYLOAD_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "CmdMode.h"
#include "GlobalMy.h"
#include <Arduino.h>
struct CommandPayload
{
	CmdMode cmdName;
	long createdAt;
	long* lastUpdated;
	int* lastStatus;

	int hardwarePin;
	long durationMs;
	long intervalMs;

	CommandPayload(CmdMode mod)
	{
		this->cmdName = mod;
	}
	~CommandPayload() {}
};

#endif

