#include <Arduino.h>
#include "settings.h"
#include "odometry.h"
#include "mouse.h"
#include "utils.h"

/* Odometric calculation variables */
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

float localX = 0;
float localY = 0;
float localTheta = 0;

bool convertMouseData()
{
  dxmm = maxMag(leftdxraw, rightdxraw) * MM_PER_COUNT;
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
  if (alpha == 0 || alpha == PI)
    return abs(x);
  else
    return y / sin(alpha);
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

float calcXMovement(float radius, float alpha, float dT, float offset)
{
  return radius * sgn(dT) * (sin(alpha + dT) - sin(alpha)) + offset;
}

float calcYMovement(float radius, float alpha, float dT)
{
  return radius * sgn(dT) * (cos(alpha) - cos(alpha + dT));
}

bool calculateDeltas() // try and optimize this in the future, takes up significant processing time
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

    dx = (calcXMovement(radiusL, alphaL, dTheta, -SENSOR_DISTANCE/2) + calcXMovement(radiusR, alphaR, dTheta, SENSOR_DISTANCE/2)) / 2;
    dy = (calcYMovement(radiusL, alphaL, dTheta) + calcYMovement(radiusR, alphaR, dTheta)) / 2;
  }

  return true;
}

bool calculatePosition()
{
  localX += dx;
  localY += dy;
  localTheta += dTheta;

  absoluteX = absoluteX + sqrt(pow(dx, 2) + pow(dy, 2)) * cos(absoluteTheta + atan2(dy, dx));
  absoluteY = absoluteY + sqrt(pow(dx, 2) + pow(dy, 2)) * sin(absoluteTheta + atan2(dy, dx));
  absoluteTheta = absoluteTheta + dTheta;

  return true;
}

bool resetLocalPos() 
{
  localX = 0;
  localY = 0;
  localTheta = 0;

  return true;
}
