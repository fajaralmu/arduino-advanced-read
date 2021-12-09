#pragma once
#ifndef _SERVOEXT_h
#define _SERVOEXT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
class ServoExtended : public Servo
{
public:
	int pin;
	ServoExtended(int pin)
	{
		this->pin = pin;
		this->attach(pin);
	}
};

#endif

