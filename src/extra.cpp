#include <Arduino.h>
#include "settings.h"
#include "mouse.h"
#include "odometry.h"
#include "pid.h"
#include "extra.h"

int sgn(float number)
{
  if (number == 0)
    return 0;
  else
    return number / abs(number);
}

void debug()
{
  Serial.println("///////////////////////////");
  Serial.println();
  Serial.print("LEFT_DX ");
  Serial.println(leftdxraw);
  Serial.print("LEFT_DY ");
  Serial.println(leftdyraw);
  Serial.print("RIGHT_DX ");
  Serial.println(rightdxraw);
  Serial.print("RIGHT_DY ");
  Serial.println(rightdyraw);

  Serial.println();
  Serial.print("X   ");
  Serial.println(absoluteX);
  Serial.print("Y   ");
  Serial.println(absoluteY);
  Serial.print("ROT ");
  Serial.println(degrees(absoluteTheta));

  Serial.println();
  Serial.print("ERROR ");
  Serial.println(error);
  Serial.print("PTERM   ");
  Serial.println(PTerm);
  Serial.print("INTGRL ");
  Serial.println(integral);
  Serial.print("ITERM ");
  Serial.println(ITerm);
  Serial.print("DTERM ");
  Serial.println(DTerm);
  Serial.print("PID ");
  Serial.println(PTerm + ITerm + DTerm);
}