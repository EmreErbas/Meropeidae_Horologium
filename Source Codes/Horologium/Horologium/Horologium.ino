#include "HAL_nixiePanel.h"

nixiePanel myNixiePanel = nixiePanel();

void setup() 
{
  myNixiePanel.begin();
  
}


void loop() 
{
  uint32_t lineX;

  while(1)
  {
    myNixiePanel.myGFX.fillScreen(0);
    
    myNixiePanel.myGFX.drawCircle(17, 7, (lineX % 16), 255); 
    //myNixiePanel.myGFX.drawCircle(17, 7, (lineX % 16), 255);
    //myNixiePanel.myGFX.writeFastVLine(0, 35, (lineX % 16), 255);
    //myNixiePanel.myGFX.drawCircle(0, (lineX % 16), 35, 14 - (lineX % 16), 255);
    myNixiePanel.demoFont();
    lineX ++;
  }

}