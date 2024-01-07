unsigned long prevMillis = 0;
unsigned long startMillis = 0;

const unsigned int LEFT_MOUSE_CLOCK = 8;
const unsigned int LEFT_MOUSE_DATA = 9;

const unsigned int RIGHT_MOUSE_CLOCK = 12;
const unsigned int RIGHT_MOUSE_DATA = 11;

/* Odometric calculation variables */
float leftdxraw = 106;
float leftdyraw = 604;
float rightdxraw = 101;
float rightdyraw = 356;

float dxmm = 0;
float leftdymm = 0;
float rightdymm = 0;

float alphaL = 0;
float alphaR = 0;

float arclengthL = 0;
float arclengthR = 0;

float radiusL = 0;
float radiusR = 0;

float gamma = 0;

float dx = 0;
float dy = 0;
float dTheta = 0;

float absoluteX = 0;
float absoluteY = 0;
float absoluteTheta = 0;

/* Odometric calculation constants */
const int SENSOR_DISTANCE = 106; // Distance between two mouse sensors, in millimeters
const float MM_PER_COUNT = 0.2;  // Number of millimeters corresponding to one count of the optical sensor

/* PID Tuning constants */
const float P_GAIN = 0;
const float I_GAIN = 0;
const float D_GAIN = 0;

/* PID calulation variables */
float PTerm = 0;
float ITerm = 0;
float DTerm = 0;
float error = 0;
float integral = 0;
float derivative = 0;

/* General program and logic constants | All in milliseconds */
const unsigned int MOUSE_POLL_RATE = 30; // Delay between sensor data requests
// const unsigned int ODOMETRY_CALC_RATE = // Frequency at which to run odometry calculations to update locaton data
const unsigned int PID_ITERATION_RATE = 100; // Frequency of PID and path correction algorithm
const bool DYNAMIC_PID_RATE = false;         // use when error exceeds something only; include min/max rate