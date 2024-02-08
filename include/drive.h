#ifndef DRIVE_H
#define DRIVE_H

#include <Servo.h>

extern unsigned long prevMillis;
extern unsigned long startMillis;

extern unsigned long lastPoll;
extern unsigned long lastLocationCalc;

bool attachServos();

// possibly? works with negative values | test first
bool setServoSpeeds(unsigned int leftSpeed, unsigned int rightSpeed);

bool driveStraight(int distance);

bool turn(double angle);

#endif