#include <Arduino.h>
#include <PS2MouseHandler.h>
#include <Servo.h>
#include <headers.h>

PS2MouseHandler leftmouse(LEFT_MOUSE_CLOCK, LEFT_MOUSE_DATA, PS2_MOUSE_STREAM);
PS2MouseHandler rightmouse(RIGHT_MOUSE_CLOCK, RIGHT_MOUSE_DATA, PS2_MOUSE_STREAM);

Servo leftservo;
Servo rightservo;

void debug()
{
  Serial.println("///////////////////////////");
  Serial.println();
  Serial.println(leftdxraw);
  Serial.println(leftdyraw);
  Serial.println(rightdxraw);
  Serial.println(rightdyraw);

  Serial.println();
  Serial.println(absoluteX);
  Serial.println(absoluteY);
  Serial.println(degrees(absoluteTheta));
}

int sgn(float number)
{
  if (number == 0)
    return 0;
  else
    return number / abs(number);
}

bool initializeMice()
{
  if (leftmouse.initialise() != 0)
  {
    Serial.println("mouse error");
  };

  delay(100);

  if (rightmouse.initialise() != 0)
  {
    Serial.println("mouse error");
  };

  return true;
}

bool attachServos()
{
  leftservo.attach(LEFT_SERVO_PIN);
  leftservo.write(LEFT_SERVO_NOMINAL);

  rightservo.attach(RIGHT_SERVO_PIN);
  rightservo.write(RIGHT_SERVO_NOMINAL);

  return true;
}

bool storeMouseData()
{
  leftmouse.get_data();
  rightmouse.get_data();

  leftdxraw += leftmouse.x_movement();
  leftdyraw += leftmouse.y_movement();
  rightdxraw += rightmouse.x_movement();
  rightdyraw += rightmouse.y_movement();

  return true;
}

bool flushMouseData()
{
  leftmouse.get_data();
  rightmouse.get_data();

  leftdxraw = 0;
  leftdyraw = 0;
  rightdxraw = 0;
  rightdyraw = 0;

  return true;
}

bool convertMouseData()
{
  dxmm = (leftdxraw + rightdxraw) / 2 * MM_PER_COUNT;
  leftdymm = leftdyraw * MM_PER_COUNT * -1;
  rightdymm = rightdyraw * MM_PER_COUNT * -1;

  return true;
}

float calcAlpha(float x, float y)
{
  return atan2(y, x);
}

float calcArcLength(float x, float y, float alpha)
{
  if (alpha == 0 || alpha == 3.1415927410125732)
  {
    return abs(x);
  }
  else
  {
    return y / sin(alpha);
  }
}

float calcRotation(float dyL, float dyR, float aL, float aR, float lL, float lR, int D)
{
  gamma = abs(aL - aR);

  return sgn(dyR - dyL) * (sqrt(pow(lL, 2) + pow(lR, 2) - (2 * cos(gamma) * lL * lR))) / D;
}

float calcRadius(float arclength, float dT)
{
  return arclength / abs(dT);
}

float calcXMovement(float radius, float alpha, float dT)
{
  return radius * sgn(dT) * (sin(alpha + dT) - sin(alpha));
}

float calcYMovement(float radius, float alpha, float dT)
{
  return radius * sgn(dT) * (cos(alpha) - cos(alpha + dT));
}

bool calculateDeltas()
{
  alphaL = calcAlpha(dxmm, leftdymm);
  alphaR = calcAlpha(dxmm, rightdymm);

  arclengthL = calcArcLength(dxmm, leftdymm, alphaL);
  arclengthR = calcArcLength(dxmm, rightdymm, alphaR);

  dTheta = calcRotation(leftdymm, rightdymm, alphaL, alphaR, arclengthL, arclengthR, SENSOR_DISTANCE);

  if (dTheta == 0)
  {
    dx = 0;
    dy = (leftdymm + rightdymm) / 2; // shouldnt have to average; sides should be equal
  }
  else
  {
    radiusL = calcRadius(arclengthL, dTheta);
    radiusR = calcRadius(arclengthR, dTheta);

    dx = (calcXMovement(radiusL, alphaL, dTheta) + calcXMovement(radiusR, alphaR, dTheta)) / 2;
    dy = (calcYMovement(radiusL, alphaL, dTheta) + calcYMovement(radiusR, alphaR, dTheta)) / 2;
  }

  return true;
}

bool calculatePosition()
{
  absoluteX = absoluteX + sqrt(pow(dx, 2) + pow(dy, 2)) * cos(absoluteTheta + atan2(dy, dx));
  absoluteY = absoluteY + sqrt(pow(dx, 2) + pow(dy, 2)) * sin(absoluteTheta + atan2(dy, dx));
  absoluteTheta = absoluteTheta + dTheta;

  return true;
}

float calcPID(float setpoint, float measured_value, float derivative)
{
  error = setpoint - measured_value; // error in millimeters

  PTerm = P_GAIN * error;

  // integral = (integral + error * PID_ITERATION_RATE);
  // ITerm = I_GAIN * integral;

  DTerm = D_GAIN * derivative;

  return PTerm + ITerm + DTerm; // returns values relative to millimeter error
}

// possibly? works with negative values | test first
bool setServoSpeeds(unsigned int leftSpeed, unsigned int rightSpeed)
{
  left_servo_speed = leftSpeed;
  right_servo_speed = rightSpeed;

  leftservo.write(LEFT_SERVO_NOMINAL + leftSpeed + (sgn(leftSpeed) * (LEFT_SERVO_OFFSET)));
  rightservo.write(RIGHT_SERVO_NOMINAL - rightSpeed - (sgn(rightSpeed) * (RIGHT_SERVO_OFFSET)));

  return true;
}

// just make it work ok
bool changeServoSpeeds(float value)
{
  // going to give us how many millimeters we need to correct by.

  value /= 10; // convert the correction factor to centimeters

  // for every centimter, modify servo speeds by one
  // float negative - turn left; positive right
  setServoSpeeds(left_servo_speed - round(value), right_servo_speed + round(value));

  return true;
}

bool driveStraight(int distance)
{
  setServoSpeeds(0, 0);

  delay(100);

  flushMouseData();

  delay(100);

  /* start servos at some arbitrary value,
  and CHANGE that value after succecctions of instructions
  ; optimal speed var or smth? */
  setServoSpeeds(LEFT_SERVO_START, RIGHT_SERVO_START);

  /* this is going to need a seperation between
   absolute coords and aboslute relative coords */

  lastPoll = 0;
  lastPID = 0;

  do
  {
    if (millis() - lastPoll >= MOUSE_POLL_RATE)
    {
      lastPoll = millis();
      storeMouseData();
    }

    if (millis() - lastPID >= PID_ITERATION_RATE)
    {
      lastPID = millis();

      convertMouseData();
      calculateDeltas();
      calculatePosition();

      changeServoSpeeds(calcPID(0, absoluteX, tan(absoluteTheta)));

      flushMouseData(); // test before and after updating speeds
    }
  } while (absoluteY < distance);

  setServoSpeeds(LEFT_SERVO_NOMINAL, RIGHT_SERVO_NOMINAL);

  return true;
}

void setup()
{
  attachServos();

  Serial.begin(9600);

  while (!Serial)
  {
    ; // wait for Serial to initialize
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  initializeMice();

  while (digitalRead(BUTTON_PIN) == HIGH);

  delay(1000);

  driveStraight(500);
}

void loop()
{
}