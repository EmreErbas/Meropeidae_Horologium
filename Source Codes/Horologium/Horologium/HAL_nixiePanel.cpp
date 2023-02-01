#include "HAL_nixiePanel.h"

/**************************************************************************/
/*!
    @brief Constructor for nixiePanel
*/
/**************************************************************************/
nixiePanel::nixiePanel(void)
{}

/**************************************************************************/
/*!
    @brief Initialize hardware and clear display
*/
/**************************************************************************/
bool nixiePanel::begin(void) 
{
  // Altered bus uses the same data line but has different clock line. If the code wants to
  // reach another drivers that have the same IDs, it needs to change the clock line.
  DefaultLine.setPins(defaultLine_SDA, defaultLine_SCK);
  AlteredLine.setPins(alteredLine_SDA, alteredLine_SCK);

  driverLeftTop.begin(driverLeftTop_ID, &DefaultLine);
  driverRightTop.begin(driverRightTop_ID, &DefaultLine);
  driverLeftTop.hardClear();
  driverRightTop.hardClear();
  driverLeftTop.end();
  driverRightTop.end(); 

  driverLeftBottom.begin(driverLeftBottom_ID, &AlteredLine);  
  driverRightBottom.begin(driverRightBottom_ID, &AlteredLine);
  driverLeftBottom.hardClear();
  driverRightBottom.hardClear();
  driverLeftBottom.end();
  driverRightBottom.end(); 
  return true;
}

void nixiePanel::updateScreen(void) 
{
  uint8_t pixelArrayBuffer1[1 + PixelsGrouped], 
          pixelArrayBuffer2[1 + (PixelsTotal - PixelsGrouped)],
          pixelArrayBuffer3[1 + PixelsGrouped], 
          pixelArrayBuffer4[1 + (PixelsTotal - PixelsGrouped)];
  
  pixelArrayBuffer1[0] = ISSI_PIXEL_StartAddress;
  pixelArrayBuffer3[0] = ISSI_PIXEL_StartAddress;
    
  pixelArrayBuffer2[0] = ISSI_PIXEL_StartAddress + PixelsGrouped;
  pixelArrayBuffer4[0] = ISSI_PIXEL_StartAddress + PixelsGrouped;

  //For top-left and top-right drivers. Rotating, scaling, grouping and sending
  driverLeftTop.begin(driverLeftTop_ID, &DefaultLine);
  driverRightTop.begin(driverRightTop_ID, &DefaultLine);  
  for (uint8_t y = 0; y < 9; y++)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      if(x < 8)
      {
        if(x + (y << 4) < PixelsGrouped)
        {
          pixelArrayBuffer1[1 + x + (y << 4)] = myGFX.ScreenBuffer[y + 8][7 - x];
          pixelArrayBuffer3[1 + x + (y << 4)] = myGFX.ScreenBuffer[18 + (y + 8)][7 - x];
        }
        else
        {
          pixelArrayBuffer2[1 + x + (y << 4) - PixelsGrouped] = myGFX.ScreenBuffer[y + 8][7 - x];
          pixelArrayBuffer4[1 + x + (y << 4) - PixelsGrouped] = myGFX.ScreenBuffer[18 + (y + 8)][7 - x];
        }        
      }
      else
      {
        if(x + (y << 4) < PixelsGrouped)
        {
          pixelArrayBuffer1[1 + x + (y << 4)] = myGFX.ScreenBuffer[y][15 - x];
          pixelArrayBuffer3[1 + x + (y << 4)] = myGFX.ScreenBuffer[18 + y][15 - x];
        }
        else
        {
          pixelArrayBuffer2[1 + x + (y << 4) - PixelsGrouped] = myGFX.ScreenBuffer[y][15 - x];
          pixelArrayBuffer4[1 + x + (y << 4) - PixelsGrouped] = myGFX.ScreenBuffer[18 + y][15 - x];  
        }    
      }
    }
  }   
  driverLeftTop.selectBank(0);
  driverLeftTop._i2c_dev->write(pixelArrayBuffer1, 1 + PixelsGrouped);
  driverLeftTop._i2c_dev->write(pixelArrayBuffer2, 1 + (PixelsTotal - PixelsGrouped));

  driverRightTop.selectBank(0);
  driverRightTop._i2c_dev->write(pixelArrayBuffer3, 1 + PixelsGrouped);
  driverRightTop._i2c_dev->write(pixelArrayBuffer4, 1 + (PixelsTotal - PixelsGrouped));

  driverLeftTop.end();
  driverRightTop.end();

  //For bottom-left and bottom-right drivers. Rotating, scaling, grouping and sending
  driverLeftBottom.begin(driverLeftBottom_ID, &AlteredLine);  
  driverRightBottom.begin(driverRightBottom_ID, &AlteredLine);
  for (uint8_t y = 0; y < 9; y++)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      if(x < 8)
      {
        if((15 - x) + ((8 - y) << 4) < PixelsGrouped)
        {
          pixelArrayBuffer1[1 + (15 - x) + ((8 - y) << 4)] = myGFX.ScreenBuffer[y + 8][8 + (7 - x)];
          pixelArrayBuffer3[1 + (15 - x) + ((8 - y) << 4)] = myGFX.ScreenBuffer[18 + (y + 8)][8 + (7 - x)];
        }
        else
        {
          pixelArrayBuffer2[1 + (15 - x) + ((8 - y) << 4) - PixelsGrouped] = myGFX.ScreenBuffer[y + 8][8 + (7 - x)];
          pixelArrayBuffer4[1 + (15 - x) + ((8 - y) << 4) - PixelsGrouped] = myGFX.ScreenBuffer[18 + (y + 8)][8 + (7 - x)];
        }   
      }
      else
      {
        if((15 - x) + ((8 - y) << 4) < PixelsGrouped)
        {
          pixelArrayBuffer1[1 + (15 - x) + ((8 - y) << 4)] = myGFX.ScreenBuffer[y][8 + (15 - x)];
          pixelArrayBuffer3[1 + (15 - x) + ((8 - y) << 4)] = myGFX.ScreenBuffer[18 + y][8 + (15 - x)];
        }
        else
        {
          pixelArrayBuffer2[1 + (15 - x) + ((8 - y) << 4) - PixelsGrouped] = myGFX.ScreenBuffer[y][8 + (15 - x)];
          pixelArrayBuffer4[1 + (15 - x) + ((8 - y) << 4) - PixelsGrouped] = myGFX.ScreenBuffer[18 + y][8 + (15 - x)]; 
        } 
      }
    }
  }
  driverLeftBottom.selectBank(0);
  driverLeftBottom._i2c_dev->write(pixelArrayBuffer1, 1 + PixelsGrouped);
  driverLeftBottom._i2c_dev->write(pixelArrayBuffer2, 1 + (PixelsTotal - PixelsGrouped));

  driverRightBottom.selectBank(0);
  driverRightBottom._i2c_dev->write(pixelArrayBuffer3, 1 + PixelsGrouped);
  driverRightBottom._i2c_dev->write(pixelArrayBuffer4, 1 + (PixelsTotal - PixelsGrouped));

  driverLeftBottom.end();
  driverRightBottom.end();
}
