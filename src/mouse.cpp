#include <Arduino.h>
#include "settings.h"
#include "mouse.h"

PS2MouseHandler leftmouse(LEFT_MOUSE_CLOCK, LEFT_MOUSE_DATA, PS2_MOUSE_STREAM);
PS2MouseHandler rightmouse(RIGHT_MOUSE_CLOCK, RIGHT_MOUSE_DATA, PS2_MOUSE_STREAM);

float leftdxraw = 0;
float leftdyraw = 0;
float rightdxraw = 0;
float rightdyraw = 0;

/*
 * Initializes both mice with small delay for
 * stability and epic startup effect
 *
 * Enable serial before calling this function
 * 
 * Returns false if at least one mouse fails to initialize
 */
bool initializeMice()
{
  bool initializeFail = false;

  if (leftmouse.initialise() != 0)
  {
    Serial.println("left mouse error");
    initializeFail = true;
  };

  delay(100);

  if (rightmouse.initialise() != 0)
  {
    Serial.println("right mouse error");
    initializeFail = true;
  };
  
  if (initializeFail == true)
    return false;
  else
    return true;
}

/*
 * Requests deltaX and deltaY data from both mice and ADDS it to the respective variables
 *
 * Note that this is raw mouse data and needs to be
 * converted via convertMouseData() before use in calculateDeltas()
 */
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

/*
 * Pulls data from both mice to wipe the memory,
 * and resets all mouse raw variables to 0
 *
 * Run before movement begins to erase any sensor data from external movement
 */
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