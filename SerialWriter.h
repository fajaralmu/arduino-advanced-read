// SerialWriter.h

#ifndef _SERIALWRITER_h
#define _SERIALWRITER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "CmdMode.h"
#include "GlobalMy.h"

void serialWrite(char* value = nullptr);
void serialWriteLn(char* value = nullptr);
void serialWrite(int value);
void serialWriteLn(int value);

void serialWriteLn(char* label, int value);
void serialWriteLn(char* label, char* value);

void serialWriteResponse( CmdMode mode, char* response );
void serialWriteResponse( CmdMode mode, int response );

#endif
