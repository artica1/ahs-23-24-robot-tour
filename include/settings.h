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
const unsigned int RIGHT_SERVO_NOMINAL = 87;

const unsigned int LEFT_SERVO_OFFSET = 5;
const unsigned int RIGHT_SERVO_OFFSET = 6;

const unsigned int LEFT_SERVO_SPEED = 2;
const unsigned int RIGHT_SERVO_SPEED = 2;

/* Odometric calculation constants */
const int SENSOR_DISTANCE = 106;   // Distance between two mouse sensors, in millimeters
const float MM_PER_COUNT = 0.0671; // Number of millimeters corresponding to one count of the optical sensor
const float LEFT_COUNTS_PER_PI = 5900;
const float RIGHT_COUNTS_PER_PI = 6300; 

/* General program and logic constants | All in milliseconds */
const unsigned int MOUSE_POLL_RATE = 20; // Delay between sensor data requests

#endif