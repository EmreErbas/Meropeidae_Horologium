#include "HAL_nixiePanel.h"

nixiePanel myNixiePanel = nixiePanel();

void setup() 
{
  myNixiePanel.begin();
  
}


void loop() 
{
  myNixiePanel.demoFont();
}