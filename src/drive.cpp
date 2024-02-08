#include <Arduino.h>
#include "settings.h"
#include "drive.h"
#include "mouse.h"
#include "odometry.h"
#include "utils.h"

Servo leftservo;
Servo rightservo;

/* Loop utility variabiles */
unsigned long prevMillis = 0;
unsigned long startMillis = 0;

unsigned long lastPoll = 0;
unsigned long lastLocationCalc = 0;

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

bool driveStraight(int distance)
{
  return true;
}

bool turn(double angle)
{
  setServoSpeeds(0, 0);

  localTheta = 0;

  delay(100);

  flushMouseData();

  delay(100);

  if (angle > 0)
    setServoSpeeds(0, RIGHT_SERVO_SPEED);
  else if (angle < 0)
    setServoSpeeds(LEFT_SERVO_SPEED, 0);
  else
    return true; // technically we did turn 0 degrees

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

      localTheta = localTheta + dTheta;

      debug();

      flushMouseData();
    }
  } while (abs(localTheta) < abs(angle));

  setServoSpeeds(0, 0);

  return true;
}