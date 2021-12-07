#include "DCMotor.h"

void DCMotor::begin()
  {
    pinMode(this->in1Pin, OUTPUT);
    pinMode(this->in2Pin, OUTPUT);
    pinMode(this->envPin, OUTPUT);

  }

  void DCMotor::turnOn(int dir)
  {
    this->dir = dir;
    if (dir == 1)
    {
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
    }
    else
    {
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
    }
  }

  void DCMotor::turnOff()
  {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
  }

  void DCMotor::write(int speed)
  {
    this->speed = speed;
    analogWrite(envPin, speed);
  }
