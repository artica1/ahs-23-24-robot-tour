#include <Arduino.h>
#include "settings.h"
#include "pid.h"
#include "drive.h"

float PTerm = 0;
float ITerm = 0;
float DTerm = 0;
float error = 0;
float integral = 0;

float calcPID(float setpoint, float measured_value, float rotation)
{
  /*
  error = setpoint - measured_value; // error in millimeters

  PTerm = P_GAIN * error;

  integral = integral + (error * PID_ITERATION_RATE);
  ITerm = I_GAIN * integral;

  DTerm = D_GAIN * tan(rotation);

  return PTerm + ITerm + DTerm; // returns values relative to millimeter error
  */

  if (measured_value > 0) setServoSpeeds(LEFT_SERVO_NOMINAL, RIGHT_SERVO_NOMINAL - 6);
  else if (measured_value < 0) setServoSpeeds(LEFT_SERVO_NOMINAL + 6, RIGHT_SERVO_NOMINAL);
  
  return true;
}
