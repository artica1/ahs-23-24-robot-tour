#ifndef DRIVE_H
#define DRIVE_H

#include <Servo.h>

extern unsigned long lastPoll;

bool attachServos();

// possibly? works with negative values | test first
bool setServoSpeeds(unsigned int leftSpeed, unsigned int rightSpeed);

bool driveStraight(int distance);

bool turnLeft(double angle);

bool turnRight(double angle);

#endif