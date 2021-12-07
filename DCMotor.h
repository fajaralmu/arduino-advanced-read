#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include <Arduino.h>

class DCMotor
{
public:
	int in1Pin;
	int in2Pin;
	int envPin;
	int dir;
	int speed;

	DCMotor(int in1, int in2, int env)
	{
		this->in1Pin = in1;
		this->in2Pin = in2;
		this->envPin = env;
	}

	void begin();
	void turnOff();

	void write(int speed);

	void turnOn(int dir);
};
