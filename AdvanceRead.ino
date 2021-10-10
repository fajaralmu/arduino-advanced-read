/*
 Name:		AdvanceRead.ino
 Created:	10/9/2021 10:18:08 PM
 Author:	Republic Of Gamers
*/

// the setup function runs once when you press reset or power the board


#include "Process.h"
#include <Arduino.h>

#define BAUD_RATE	9600
bool started = false;
void setup() {
	Serial.begin(BAUD_RATE);
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	if (Serial.available() > 0) {
		if (started == false) {
			preProccess();
			
			started = true;
		}
		int input = Serial.read();
		processInput(input);
	}
	checkCurrentCommand();
	applyCommands();
	delay(1);
}
