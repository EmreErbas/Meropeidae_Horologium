#include "HAL_nixiePanel.h"

nixiePanel myNixiePanel = nixiePanel();

void setup() 
{
  myNixiePanel.begin();
  
}


void loop() 
{
  float lineX;

  while(1)
  {

    myNixiePanel.myGFX.fillScreen(0);
  
    myNixiePanel.myGFX.drawGrayscaleBitmap(lineX, 2.0, 36, 16); 
    //myNixiePanel.myGFX.drawCircle(17, 7, (lineX % 16), 255);
    //myNixiePanel.myGFX.writeFastVLine(0, 35, (lineX % 16), 255);
    //myNixiePanel.myGFX.drawCircle(0, (lineX % 16), 35, 14 - (lineX % 16), 255);
    myNixiePanel.demoFont();
    lineX = lineX + 0.1;
    if(lineX > 30)
    {
      lineX = 0;
    }

  }

}