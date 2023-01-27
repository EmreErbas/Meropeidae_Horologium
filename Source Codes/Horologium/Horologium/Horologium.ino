#include "HAL_nixiePanel.h"

nixiePanel myNixiePanel = nixiePanel();

void setup() 
{
  myNixiePanel.begin();
  
}


void loop() 
{
  volatile uint32_t lineX, lineY = 10, delayX;

  while(1)
  {
    delayX = 10000000;
    while(delayX)
    {
      delayX -= 1;
    }

    myNixiePanel.myGFX.fillScreen(0);
  
    myNixiePanel.myGFX.drawGrayscaleBitmap(lineX, lineY, 36, 16); 
    //myNixiePanel.myGFX.drawCircle(17, 7, (lineX % 16), 255);
    //myNixiePanel.myGFX.writeFastVLine(0, 35, (lineX % 16), 255);
    //myNixiePanel.myGFX.drawCircle(0, (lineX % 16), 35, 14 - (lineX % 16), 255);
    myNixiePanel.demoFont();
    lineX ++;
    if(lineX > 30)
    {
      lineX = 0;
      lineY ++;
    }

  }

}