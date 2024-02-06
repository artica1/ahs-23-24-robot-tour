#include <Arduino.h>
#include "settings.h"
#include "drive.h"
#include "mouse.h"
#include "odometry.h"
#include "pid.h"
#include "utils.h"

Servo leftservo;
Servo rightservo;

/* Loop utility variabiles */
unsigned long prevMillis = 0;
unsigned long startMillis = 0;

unsigned long lastPoll = 0;
unsigned long lastPID = 0;
unsigned long lastLocationCalc = 0;

/* Servo variables */
int left_servo_speed = 0; // current RELATIVE speed of servos
int right_servo_speed = 0;

// optimal servo stuff

bool attachServos()
{
  leftservo.attach(LEFT_SERVO_PIN);
  leftservo.write(LEFT_SERVO_NOMINAL);

  rightservo.attach(RIGHT_SERVO_PIN);
  rightservo.write(RIGHT_SERVO_NOMINAL);

  return true;
}

// possibly? works with negative values | test first
bool setServoSpeeds(unsigned int leftSpeed, unsigned int rightSpeed)
{
  // left_servo_speed = leftSpeed;
  // right_servo_speed = rightSpeed;

  leftservo.write(LEFT_SERVO_NOMINAL + leftSpeed + (sgn(leftSpeed) * (LEFT_SERVO_OFFSET)));
  rightservo.write(RIGHT_SERVO_NOMINAL - rightSpeed - (sgn(rightSpeed) * (RIGHT_SERVO_OFFSET)));

  return true;
}

// just make it work ok
bool changeServoSpeeds(float value)
{
  // going to give us how many millimeters we need to correct by.

  value /= 10; // convert the correction factor to centimeters
  // value = constrain(value, -5, 5); // prevent overwind

  if (abs(value) < 1) // If value is between -1 and 1
    return true;      // Experimental | When correction factor is less than zero (near center line), dont reset the servo values, keep them the same

  // for every centimter, modify servo speeds by one
  setServoSpeeds(LEFT_SERVO_START + round(value), RIGHT_SERVO_START - round(value));

  return true;
}

bool driveStraight(int distance)
{
  setServoSpeeds(0, 0);

  delay(100);

  flushMouseData();

  delay(100);

  /* start servos at some arbitrary value,
  and CHANGE that value after succecctions of instructions
  ; optimal speed var or smth? */
  setServoSpeeds(LEFT_SERVO_START, RIGHT_SERVO_START);

  /* this is going to need a seperation between
   absolute coords and aboslute relative coords */

  lastPoll = millis();
  lastPID = millis();

  do
  {
    if (millis() - lastPoll >= MOUSE_POLL_RATE)
    {
      lastPoll = millis();

      storeMouseData();

      if (digitalRead(BUTTON_PIN) == LOW)
      {
        setServoSpeeds(0, 0);
        return false;
      }
    }

    if (millis() - lastPID >= PID_ITERATION_RATE)
    {
      lastPID = millis();

      convertMouseData();
      calculateDeltas();
      calculatePosition();

      // changeServoSpeeds(calcPID(0, absoluteX, absoluteTheta));
      calcPID(0, absoluteX, absoluteTheta);

      debug();

      flushMouseData(); // test before and after updating speeds
    }
  } while (absoluteY < 500);

  setServoSpeeds(0, 0);

  return true;
}

/* double angle? */
bool turn(double angle)
{
  setServoSpeeds(0, 0);

  delay(100);

  flushMouseData();

  delay(100);

  if (angle > 0)
    setServoSpeeds(0, TURN_SPEED);
  else if (angle < 0)
    setServoSpeeds(TURN_SPEED, 0);
  else
    return false;

  lastPoll = 0;
  lastLocationCalc = 0;

  do
  {
    if (millis() - lastPoll >= MOUSE_POLL_RATE)
    {
      lastPoll = millis();

      storeMouseData();

      if (digitalRead(BUTTON_PIN) == LOW)
      {
        setServoSpeeds(0, 0);
        return false;
      }
    }

    if (millis() - lastLocationCalc >= ODOMETRY_CALC_RATE)
    {
      lastLocationCalc = millis();

      convertMouseData();
      calculateDeltas();
      calculatePosition();

      debug();

      flushMouseData(); // test before and after updating speeds
    }
  } while (absoluteTheta < angle);

  setServoSpeeds(0, 0);

  return true;
}