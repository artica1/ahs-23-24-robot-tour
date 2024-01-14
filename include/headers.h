// TODO
// DEREVETIVE CONTROL
// TURN FUNCTION FULL
// SPEED
// REFACTOR

/* Loop utility variabiles */
unsigned long prevMillis = 0;
unsigned long startMillis = 0;

unsigned long lastPoll = 0;
unsigned long lastPID = 0;

/* Pin assignments */
const unsigned int LEFT_MOUSE_CLOCK = 8;
const unsigned int LEFT_MOUSE_DATA = 9;

const unsigned int RIGHT_MOUSE_CLOCK = 12;
const unsigned int RIGHT_MOUSE_DATA = 11;

const unsigned int LEFT_SERVO_PIN = 5;
const unsigned int RIGHT_SERVO_PIN = 6;

const unsigned int BUTTON_PIN = 13;

/* Servo constants */
const unsigned int LEFT_SERVO_NOMINAL = 90;
const unsigned int RIGHT_SERVO_NOMINAL = 90;

// should be one below the value the servo starts spinning at
const unsigned int LEFT_SERVO_OFFSET = 5; 
const unsigned int RIGHT_SERVO_OFFSET = 5;

const unsigned int LEFT_SERVO_START = 5;
const unsigned int RIGHT_SERVO_START = 5;

/* Odometric calculation constants */
const unsigned int SENSOR_DISTANCE = 106; // Distance between two mouse sensors, in millimeters
const float MM_PER_COUNT = 0.1; // Number of millimeters corresponding to one count of the optical sensor

/* Servo variables */
int left_servo_speed = 0; // current RELATIVE speed of servos
int right_servo_speed = 0;

// optimal servo stuff

/* Odometric calculation variables */
float leftdxraw = 0;
float leftdyraw = 0;
float rightdxraw = 0;
float rightdyraw = 0;

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

/* PID Tuning constants */
const float P_GAIN = -1;
const float I_GAIN = 1;
const float D_GAIN = 1;

/* PID calulation variables */
float PTerm = 0;
float ITerm = 0;
float DTerm = 0;
float error = 0;
//float integral = 0;
//float derivative = 0;

/* General program and logic constants | All in milliseconds */
const unsigned int MOUSE_POLL_RATE = 30; // Delay between sensor data requests
const unsigned int ODOMETRY_CALC_RATE = -1; // Frequency at which to run odometry calculations to update locaton data
const unsigned int PID_ITERATION_RATE = 1000; // Frequency of PID and path correction algorithm
const bool DYNAMIC_PID_RATE = false;         // use when error exceeds something only; include min/max rate