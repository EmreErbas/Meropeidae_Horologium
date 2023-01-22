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
  // https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf#page=48
  // https://github.com/EmreErbas/Meropeidae_Horologium/blob/main/Documents/Notes/03-How%20to%20program%20ESP32-S3.md
  DefaultLine.setPins(3, 4);
  AlteredLine.setPins(3, 5);

  driverLeftTop.begin(0x77, &DefaultLine);
  driverRightTop.begin(0x74, &DefaultLine);
  driverLeftTop.hardClear();
  driverRightTop.hardClear();
  driverLeftTop.end();
  driverRightTop.end(); 

  driverLeftBottom.begin(0x77, &AlteredLine);  
  driverRightBottom.begin(0x74, &AlteredLine);
  driverLeftBottom.hardClear();
  driverRightBottom.hardClear();
  driverLeftBottom.end();
  driverRightBottom.end(); 
  return true;
}


void nixiePanel::demoShow(void) 
{
  // The lookup table to make the brightness changes be more visible
  const static uint8_t sweep[] = 
  {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 29, 32, 35, 38, 41, 44, 
    47, 44, 41, 38, 35, 32, 29, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 7, 6, 5, 4, 3, 2, 1
  };

  driverLeftTop.begin(0x77, &DefaultLine);
  driverRightTop.begin(0x74, &DefaultLine);
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {
        driverLeftTop.setLEDPWM(x + (y << 4), sweep[(x + y + incr + 2) % 48]);
      }
    }
  }
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {
        driverRightTop.setLEDPWM(x + (y << 4), sweep[(x + y + incr) % 48]);    
      }
    }
  }
  driverLeftTop.end();
  driverRightTop.end();

  driverLeftBottom.begin(0x77, &AlteredLine);  
  driverRightBottom.begin(0x74, &AlteredLine);
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {  
        driverLeftBottom.setLEDPWM(x + (y << 4), sweep[(x + y + incr + 2) % 48]); 
      }
    }
  }
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {  
        driverRightBottom.setLEDPWM(x + (y << 4), sweep[(x + y + incr) % 48]); 
      }
    }
  }
  driverLeftBottom.end();
  driverRightBottom.end();
}

void nixiePanel::demoFont(void) 
{
  myGFX.writeLine(0, 0, 3, 4, 50);

  uint16_t pixelLookUpTable[16][9] = {
  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
  {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000}
  };

  driverLeftTop.begin(0x77, &DefaultLine);
  driverRightTop.begin(0x74, &DefaultLine);
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {
        if(x < 8)
        {
          driverLeftTop.setLEDPWM(x + (y << 4), myGFX.ScreenBuffer[x][y]);
        }
        else
        {
          driverLeftTop.setLEDPWM(x + (y << 4), myGFX.ScreenBuffer[x][y]);
        }
      }
    }
  }
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {
        driverRightTop.setLEDPWM(x + (y << 4), 1);    
      }
    }
  }
  driverLeftTop.end();
  driverRightTop.end();

  driverLeftBottom.begin(0x77, &AlteredLine);  
  driverRightBottom.begin(0x74, &AlteredLine);
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {  
        driverLeftBottom.setLEDPWM(x + (y << 4), 1); 
      }
    }
  }
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {  
        driverRightBottom.setLEDPWM(x + (y << 4), 1); 
      }
    }
  }
  driverLeftBottom.end();
  driverRightBottom.end();
}
