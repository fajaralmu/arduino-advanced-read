/*
 Name:		AdvanceRead.ino
 Created:	10/9/2021 10:18:08 PM
 Author:	Republic Of Gamers
*/

// the setup function runs once when you press reset or power the board


#include "GlobalMy.h"
#include "Process.h"
#include <Arduino.h>

#define BAUD_RATE	9600
bool started = false;
void setup() {
	Serial.begin(BAUD_RATE);
}

long time = millis();
void refreshLog()
{
	long now = millis();
	if (now - time > 3000) {
		int avail = Serial.available();
		Serial.print(" (ok-");
		Serial.print(avail);
		Serial.print(") ");
		time = now;
	}
}

// the loop function runs over and over again until power down or reset
void loop() {
	int available = Serial.available();

	if (available > 0) {
		Serial.println(available);
		if (started == false) {
			preProccess();
			
			started = true;
		}
		int input = Serial.read();
		//Serial.println("<!>new input");
		processInput(input);
		checkCurrentCommand();
	}
	
	applyCommands();
	refreshLog();
	delay(10);
}
