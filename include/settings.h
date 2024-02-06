// TODO
// DEREVETIVE CONTROL
// TURN FUNCTION FULL
// SPEED
// optimal servo stuff
// make absolute be the rod

#ifndef SETTINGS_H
#define SETTINGS_H

/* Pin assignments */
const unsigned int LEFT_MOUSE_CLOCK = 8;
const unsigned int LEFT_MOUSE_DATA = 9;

const unsigned int RIGHT_MOUSE_CLOCK = 12;
const unsigned int RIGHT_MOUSE_DATA = 11;

const unsigned int LEFT_SERVO_PIN = 5;
const unsigned int RIGHT_SERVO_PIN = 6;

const unsigned int BUTTON_PIN = 13;

/* Servo constants */
const unsigned int LEFT_SERVO_NOMINAL = 87;
const unsigned int RIGHT_SERVO_NOMINAL = 88;

const unsigned int LEFT_SERVO_OFFSET = 4;
const unsigned int RIGHT_SERVO_OFFSET = 5;

const unsigned int LEFT_SERVO_START = 1;
const unsigned int RIGHT_SERVO_START = 1;

const unsigned int TURN_SPEED = 2;

/* Odometric calculation constants */
const int SENSOR_DISTANCE = 106; // Distance between two mouse sensors, in millimeters
const float MM_PER_COUNT = 0.08;         // Number of millimeters corresponding to one count of the optical sensor

/* Robot Position and Rotation Variables */
extern float absoluteX;
extern float absoluteY;
extern float absoluteTheta; // Radians

/* PID Tuning constants */
const float P_GAIN = 1;
const float I_GAIN = 0;
const float D_GAIN = 0;

/* General program and logic constants | All in milliseconds */
const unsigned int MOUSE_POLL_RATE = 20;     // Delay between sensor data requests
const unsigned int ODOMETRY_CALC_RATE = 0;  // Frequency at which to run odometry calculations to update locaton data
const unsigned int PID_ITERATION_RATE = 1000; // Frequency of PID and path correction algorithm
const bool DYNAMIC_PID_RATE = false;         // use when error exceeds something only; include min/max rate

#endif