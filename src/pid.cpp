#include <Arduino.h>
#include "settings.h"
#include "pid.h"

float PTerm = 0;
float ITerm = 0;
float DTerm = 0;
float error = 0;
float integral = 0;

float calcPID(float setpoint, float measured_value, float rotation)
{
  error = (setpoint - measured_value) * -1; // error in millimeters

  PTerm = P_GAIN * error;

  integral = integral + (error * PID_ITERATION_RATE);
  ITerm = I_GAIN * integral;

  DTerm = D_GAIN * tan(rotation);

  return PTerm + ITerm + DTerm; // returns values relative to millimeter error
}