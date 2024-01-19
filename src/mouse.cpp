#include <Arduino.h>
#include "settings.h"
#include "mouse.h"

PS2MouseHandler leftmouse(LEFT_MOUSE_CLOCK, LEFT_MOUSE_DATA, PS2_MOUSE_STREAM);
PS2MouseHandler rightmouse(RIGHT_MOUSE_CLOCK, RIGHT_MOUSE_DATA, PS2_MOUSE_STREAM);

float leftdxraw = 0;
float leftdyraw = 0;
float rightdxraw = 0;
float rightdyraw = 0;

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