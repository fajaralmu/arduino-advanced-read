// Process.h

#ifndef _PROCESS_h
#define _PROCESS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif
#include "InputParses.h"
#include "WString.h"

#ifdef __cplusplus
extern "C" {
#endif
	void preProccess();
	void processInput(int input);

#ifdef __cplusplus
}
#endif

