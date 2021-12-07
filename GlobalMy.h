// GlobalMy.h

#ifndef _GLOBALMY_h
#define _GLOBALMY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#define CMD_MAX_LENGTH	250
#define LED_PIN			13
#define COMMAND_MAX_COUNT   50
#define SERVO_A_PIN		9
#define SERVO_B_PIN		10
#define SERVO_C_PIN		11
#define MOTOR_A_PIN		9
#define MOTOR_B_PIN		3

// message transmission

#define START_OF_HEADING	"SOH"
#define START_OF_TEXT		"STX"

#define END_OF_TEXT			"ETX"
#define END_OF_TRANSMISSION	"EOT"

#define RESPONSE_OK 1
#define RESPONSE_FAILED -1
#define RESPONSE_INVALID_CMD -2


#endif

