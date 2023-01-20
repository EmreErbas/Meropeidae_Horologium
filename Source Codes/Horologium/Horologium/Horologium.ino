#include <Wire.h>
#include <Adafruit_GFX.h>
#include "HAL_nixiePanel.h"

nixiePanel myNixiePanel = nixiePanel();

void setup() 
{
  myNixiePanel.begin();
}


void loop() 
{
  myNixiePanel.demoShow();
}