#include <Arduino.h>
#include "settings.h"
#include "drive.h"
#include "mouse.h"

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
}

void loop()
{
  while (digitalRead(BUTTON_PIN) == HIGH);

  delay(1000);

  driveStraight(200);

  delay(1000);
}