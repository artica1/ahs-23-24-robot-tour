#include <Arduino.h>
#include "settings.h"
#include "mouse.h"
#include "utils.h"

/*
 * Implementation of the sgn(x) function
 *
 * Returns 1 for positive inputs, -1 for negative inputs, and 0 for an input of zero
 */
int sgn(double number)
{
  return number == 0 ? 0 : number / abs(number);
}

/*
 * Of two integers, return the one with the greatest magnitude
 *
 * For now, only works when both integers have the same sign
 */
int maxMag(int a, int b)
{
  return (abs(a) > abs(b)) ? a : b;
}

void debug()
{
  Serial.println("///////////////////////////");
  Serial.println();
  Serial.print("LEFT_DX ");
  Serial.println(leftdxraw);
  Serial.print("RIGHT_DX ");
  Serial.println(rightdxraw);
  Serial.println();
  Serial.print("LEFT_DY ");
  Serial.println(leftdyraw);
  Serial.print("RIGHT_DY ");
  Serial.println(rightdyraw);
/*
  Serial.println();
  Serial.print("DX_MM ");
  Serial.println(dxmm);
  Serial.print("LEFT_DY_MM ");
  Serial.println(leftdymm);
  Serial.print("RIGHT_DY_MM ");
  Serial.println(rightdymm);
*/
  //Serial.println();
  //Serial.print("X   ");
  //Serial.println(localX);
  //Serial.print("Y   ");
  //Serial.println(localY);
  //Serial.print("ROT ");
  //Serial.println(degrees(localTheta));

/*
  Serial.println();
  Serial.print("ERROR  ");
  Serial.println(error);
  Serial.print("PTERM  ");
  Serial.println(PTerm);
  Serial.print("INTGRL ");
  Serial.println(integral);
  Serial.print("ITERM  ");
  Serial.println(ITerm);
  Serial.print("DTERM  ");
  Serial.println(DTerm);
  Serial.print("PID ");
  Serial.println(PTerm + ITerm + DTerm);
  */
}

void debugEnd() 
{
  /*
  Serial.println("///////////////////////////");
  Serial.println("FINAL FINAL FINAL FINAL FINAL");
  Serial.println();
  Serial.print("LEFT_DX TOTAL ");
  Serial.println(leftdxraw_TOTAL);
  Serial.print("RIGHT_DX TOTAL ");
  Serial.println(rightdxraw_TOTAL);
  Serial.println();
  Serial.print("LEFT_DY TOTAL ");
  Serial.println(leftdyraw_TOTAL);
  Serial.print("RIGHT_DY TOTAL ");
  Serial.println(rightdyraw_TOTAL);
  

  Serial.println();
  Serial.print("LEFT_DX_MM TOTAL ");
  Serial.println(leftdxraw_TOTAL * MM_PER_COUNT);
  Serial.print("RIGHT_DX_MM TOTAL ");
  Serial.println(rightdxraw_TOTAL * MM_PER_COUNT);
  Serial.println();
  Serial.print("LEFT_DY TOTAL_MM ");
  Serial.println(leftdyraw_TOTAL * MM_PER_COUNT * -1);
  Serial.print("RIGHT_DY TOTAL_MM ");
  Serial.println(rightdyraw_TOTAL * MM_PER_COUNT * -1);
  */
}

void debugLeft()
{
  Serial.println("///////////////////////////");
  Serial.println();
  Serial.print("LEFT_DX ");
  Serial.println(leftdxraw);
  Serial.println();
  Serial.print("LEFT_DY ");
  Serial.println(leftdyraw);
}

void debugRight()
{
  Serial.println("///////////////////////////");
  Serial.println();
  Serial.print("RIGHT_DX ");
  Serial.println(rightdxraw);
  Serial.println();
  Serial.print("RIGHT_DY ");
  Serial.println(rightdyraw);
}