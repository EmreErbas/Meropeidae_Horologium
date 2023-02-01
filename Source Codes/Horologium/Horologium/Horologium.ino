#include "HAL_nixiePanel.h"

nixiePanel myNixiePanel = nixiePanel();

void setup() 
{
  myNixiePanel.begin();

  myNixiePanel.myGFX.setFont(&FreeSansOblique9pt7b);
  myNixiePanel.myGFX.fillScreen(0);
  myNixiePanel.myGFX.println("E");
  myNixiePanel.demoFont();
}


void loop() 
{
  float lineX;

  while(1)
  {


    
 // myNixiePanel.myGFX.fillScreen(0);


  //  myNixiePanel.myGFX.setFont(&FreeMono12pt7b);
    //myNixiePanel.myGFX.drawChar(0, 0, 'E', 0xFF, 0x00, 1);
  


  //  myNixiePanel.myGFX.drawGrayscaleBitmap(lineX, 2.0, 36, 16); 
    //myNixiePanel.myGFX.drawCircle(17, 7, (lineX % 16), 255);
    //myNixiePanel.myGFX.writeFastVLine(0, 35, (lineX % 16), 255);
    //myNixiePanel.myGFX.drawCircle(0, (lineX % 16), 35, 14 - (lineX % 16), 255);
  //  myNixiePanel.demoFont();
    lineX = lineX + 0.1;
    if(lineX > 30)
    {
      lineX = 0;
    }

  }

}