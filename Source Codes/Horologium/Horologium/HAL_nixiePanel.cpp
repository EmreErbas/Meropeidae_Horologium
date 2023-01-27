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
  driverLeftTop.begin(0x77, &DefaultLine);
  driverRightTop.begin(0x74, &DefaultLine);

  uint8_t cmd1[145];
  uint8_t cmd2[145];
  
  cmd1[0] = 0x24;
  cmd2[0] = 0x24;
  
  for (uint8_t y = 0; y < 9; y++)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      if(x < 8)
      {
        cmd1[1 + x + (y << 4)] = myGFX.ScreenBuffer[y + 8][7 - x];
        cmd2[1 + x + (y << 4)] = myGFX.ScreenBuffer[18 + (y + 8)][7 - x];

      }
      else
      {
        cmd1[1 + x + (y << 4)] = myGFX.ScreenBuffer[y][15 - x];
        cmd2[1 + x + (y << 4)] = myGFX.ScreenBuffer[18 + y][15 - x];
      }
    }
  }   
  driverLeftTop.selectBank(0);
  driverLeftTop._i2c_dev->write(cmd1, 145);

  driverRightTop.selectBank(0);
  driverRightTop._i2c_dev->write(cmd2, 145);

  driverLeftTop.end();
  driverRightTop.end();

  driverLeftBottom.begin(0x77, &AlteredLine);  
  driverRightBottom.begin(0x74, &AlteredLine);
  for (uint8_t y = 0; y < 9; y++)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      if(x < 8)
      {
        cmd1[1 + (15 - x) + ((8 - y) << 4)] = myGFX.ScreenBuffer[y + 8][8 + (7 - x)];
        cmd2[1 + (15 - x) + ((8 - y) << 4)] = myGFX.ScreenBuffer[18 + (y + 8)][8 + (7 - x)];
      }
      else
      {
        cmd1[1 + (15 - x) + ((8 - y) << 4)] = myGFX.ScreenBuffer[y][8 + (15 - x)];
        cmd2[1 + (15 - x) + ((8 - y) << 4)] = myGFX.ScreenBuffer[18 + y][8 + (15 - x)];
      }
    }
  }
  driverLeftBottom.selectBank(0);
  driverLeftBottom._i2c_dev->write(cmd1, 145);

  driverRightBottom.selectBank(0);
  driverRightBottom._i2c_dev->write(cmd2, 145);

  driverLeftBottom.end();
  driverRightBottom.end();
}
