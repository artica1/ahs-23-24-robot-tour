// TODO
// wipe odometry functions of unneeded stuff
// does this need dx dy at all?

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

const unsigned int LEFT_SERVO_SPEED = 1;
const unsigned int RIGHT_SERVO_SPEED = 1;

/* Odometric calculation constants */
const int SENSOR_DISTANCE = 106; // Distance between two mouse sensors, in millimeters
const float MM_PER_COUNT = 0.08;         // Number of millimeters corresponding to one count of the optical sensor

/* General program and logic constants | All in milliseconds */
const unsigned int MOUSE_POLL_RATE = 20;     // Delay between sensor data requests
const unsigned int ODOMETRY_CALC_RATE = 100;  // Frequency at which to run odometry calculations to update locaton data

#endif