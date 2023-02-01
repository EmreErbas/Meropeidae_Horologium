#include "HAL_nixiePanel.h"

nixiePanel myNixiePanel = nixiePanel();

void setup() 
{
  myNixiePanel.begin();
  
/*
  myNixiePanel.myGFX.setFont(&FreeSansOblique9pt7b);
  myNixiePanel.myGFX.fillScreen(0);
  myNixiePanel.myGFX.println("E");
  myNixiePanel.updateScreen();
  */
}


void loop() 
{
  float lineX;

  while(1)
  {
    myNixiePanel.myGFX.fillScreen(0);

    myNixiePanel.myGFX.drawGrayscaleBitmap(lineX, 2.0, 36, 16); 

    myNixiePanel.updateScreen();

    lineX = lineX + 0.1;
    if(lineX > 30)
    {
      lineX = 0;
    }

  }

}