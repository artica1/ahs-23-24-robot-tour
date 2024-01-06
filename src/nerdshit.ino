#include <Arduino.h>
#include <PS2MouseHandler.h>
#include <Servo.h>
#include "headers.h"

PS2MouseHandler leftmouse(LEFT_MOUSE_CLOCK, LEFT_MOUSE_DATA, PS2_MOUSE_STREAM);
PS2MouseHandler rightmouse(RIGHT_MOUSE_CLOCK, RIGHT_MOUSE_DATA, PS2_MOUSE_STREAM);

Servo leftservo;
Servo rightservo;

int sgn(float number)
{
  if (number == 0)
    return 0;
  else
    return number / abs(number);
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
  leftdymm = leftdyraw * MM_PER_COUNT;
  rightdymm = rightdyraw * MM_PER_COUNT;

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

/*
float runPID(float setpoint, float input) {
  error = setpoint - input;

  PTerm = P_GAIN * error;

  integral = (integral + error * PID_ITERATION_RATE);
  ITerm = I_GAIN * integral;

  //DTerm

  return PTerm + ITerm + DTerm;
}

bool changeMotorSpeeds(float value) {
  leftservo.write(95 + value);
  rightservo.write(86 + value);
}
*/

void setup()
{
  Serial.begin(9600);

  convertMouseData();
  calculateDeltas();
  calculatePosition();

  Serial.println();
  Serial.println(dx);
  Serial.println(dy);
  Serial.println(degrees(dTheta));

  if (leftmouse.initialise() != 0)
  {
    // mouse error
    Serial.println("mouse error");
  };

  delay(100);

  if (rightmouse.initialise() != 0)
  {
    // mouse error
    Serial.println("mouse error");
  };

  pinMode(13, INPUT_PULLUP);

  leftservo.attach(5);
  leftservo.write(87);

  rightservo.attach(6);
  rightservo.write(89);
}

void loop()
{
  while (digitalRead(13) == HIGH)
  {
  }

  delay(2000);

  // for (int i = 0; i <=2; i++) {
  flushMouseData();

  leftservo.write(80);
  rightservo.write(94);

  prevMillis = 0;
  startMillis = millis();

  while (true)
  {
    if (millis() - startMillis >= 1500)
    {
      leftservo.write(87);
      rightservo.write(89);
      break;
    }

    if (millis() - prevMillis >= MOUSE_POLL_RATE)
    {
      prevMillis = millis();
      storeMouseData();
    }
  }

  convertMouseData();
  calculateDeltas();
  calculatePosition();
  // runPID();
  // updateMotorSpeeds();
  // flushMouseData(); // test before and after updating speeds

  //}

  while (digitalRead(13) == HIGH)
  {
  }

  Serial.println();
  Serial.println(leftdxraw);
  Serial.println(leftdyraw);
  Serial.println(rightdxraw);
  Serial.println(rightdyraw);

  Serial.println();
  Serial.println(absoluteX);
  Serial.println(absoluteY);
  Serial.println(absoluteTheta);

  delay(2000);
}