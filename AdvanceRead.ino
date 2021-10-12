/*
 Name:		AdvanceRead.ino
 Created:	10/9/2021 10:18:08 PM
 Author:	Republic Of Gamers
*/

// the setup function runs once when you press reset or power the board

#include "CommandPayload.h"
#include <stdio.h>
#include "GlobalMy.h"
#include "Process.h"
#include <Arduino.h>
#include <time.h> 

#define BAUD_RATE	9600
bool started = false;

unsigned long _time;

void setup() {
	Serial.begin(BAUD_RATE);
	pinMode(LED_PIN, OUTPUT);
	_time = millis();
}
 
void refreshLog()
{
	long _now = millis();
	if (_now - _time > 3000) {
		
		//int m = now
		int avail = Serial.available();
		Serial.print(" (ok-");
		Serial.print(_now);
		Serial.print(") ");
		_time = _now;
	}
}

void printWelcoming()
{
	Serial.println("========================== Welcome =========================");
}

// the loop function runs over and over again until power down or reset
void loop() {
	int available = Serial.available();

	if (available > 0) {
		if (started == false) {
			printWelcoming();
			preProccess();
			
			started = true;
		}
		int input = Serial.read();
		//Serial.println("<!>new input");
		processInput(input);
		checkCurrentCommand();
	}
	
	applyCommands();
	updateCommands();
	refreshLog();
	delay(1);
}
