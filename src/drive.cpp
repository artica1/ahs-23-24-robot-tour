#include <Arduino.h>
#include "settings.h"
#include "drive.h"
#include "mouse.h"
#include "utils.h"

Servo leftservo;
Servo rightservo;

/* Loop utility variabiles */
unsigned long lastPoll = 0;

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
  leftservo.write(LEFT_SERVO_NOMINAL + leftSpeed + (sgn(leftSpeed) * (LEFT_SERVO_OFFSET)));
  rightservo.write(RIGHT_SERVO_NOMINAL - rightSpeed - (sgn(rightSpeed) * (RIGHT_SERVO_OFFSET)));

  return true;
}

bool turnLeft(double angle)
{
  setServoSpeeds(0, 0);

  delay(100);

  flushMouseData();

  float reqCounts = angle / PI * LEFT_COUNTS_PER_PI;

  delay(100);

  setServoSpeeds(0, RIGHT_SERVO_SPEED);

  lastPoll = 0;

  while (true)
  {
    if (millis() - lastPoll >= MOUSE_POLL_RATE)
    {
      lastPoll = millis();

      storeMouseData();

      // debugLeft();

      if (digitalRead(BUTTON_PIN) == LOW)
      {
        setServoSpeeds(0, 0);
        return false;
      }

      if (abs(leftdxraw) >= reqCounts)
        break;
    }
  }

  setServoSpeeds(0, 0);

  return true;
}

bool turnRight(double angle)
{
  setServoSpeeds(0, 0);

  delay(100);

  flushMouseData();

  float reqCounts = angle / PI * RIGHT_COUNTS_PER_PI;

  delay(100);

  setServoSpeeds(LEFT_SERVO_SPEED, 0);

  lastPoll = 0;

  while (true)
  {
    if (millis() - lastPoll >= MOUSE_POLL_RATE)
    {
      lastPoll = millis();

      storeMouseData();

      // debugRight();

      if (digitalRead(BUTTON_PIN) == LOW)
      {
        setServoSpeeds(0, 0);
        return false;
      }

      if (abs(rightdxraw) >= reqCounts)
        break;
    }
  }

  setServoSpeeds(0, 0);

  return true;
}

bool driveStraight(int total_distance)
{
  if (total_distance == 0)
    return true; // are you stupid

  int n = 0;
  float cycle_distance = 0;
  int maxSegmentLength = 2 * SENSOR_DISTANCE;

  if (total_distance % maxSegmentLength == 0)
  {
    cycle_distance = maxSegmentLength;
    n = total_distance / cycle_distance;
  }
  else
  {
    cycle_distance = maxSegmentLength - ((maxSegmentLength - (total_distance % maxSegmentLength)) / ((total_distance - (total_distance % maxSegmentLength)) / (float)maxSegmentLength + 1));
    n = total_distance / cycle_distance;
  }

  for (int i = 0; i < n; i++)
  {

    double test = asin(cycle_distance / (2.0 * SENSOR_DISTANCE));

    if (isnan(test))
      return false;

    turnRight(test);
    turnLeft(2 * test);
    turnRight(test);
  }

  return true;
}