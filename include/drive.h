#ifndef DRIVE_H
#define DRIVE_H

#include <Servo.h>

extern unsigned long prevMillis;
extern unsigned long startMillis;

extern unsigned long lastPoll;
extern unsigned long lastPID;

extern int left_servo_speed;
extern int right_servo_speed;

bool attachServos();

// possibly? works with negative values | test first
bool setServoSpeeds(unsigned int leftSpeed, unsigned int rightSpeed);

// just make it work ok
bool changeServoSpeeds(float value);

bool driveStraight(int distance);

#endif