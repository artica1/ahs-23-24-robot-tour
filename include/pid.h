#ifndef PID_H
#define PID_H

/* PID calulation variables */
extern float PTerm;
extern float ITerm;
extern float DTerm;
extern float error;
extern float integral;

float calcPID(float setpoint, float measured_value, float rotation);

#endif