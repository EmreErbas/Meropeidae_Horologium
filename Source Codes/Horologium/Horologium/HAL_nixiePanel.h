#ifndef _HAL_NIXIEPANEL_H_
#define _HAL_NIXIEPANEL_H_

#include "is31fl3731.h"  
#include "Adafruit_GFX.h"

#define WIDTH  36       ///< This is the 'raw' display width  - never changes
#define HEIGHT 16       ///< This is the 'raw' display height - never changes

// https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf#page=48
#define defaultLine_SCK 4
#define defaultLine_SDA 3

#define alteredLine_SCK 5
#define alteredLine_SDA 3

#define driverLeftTop_ID     0x77
#define driverRightTop_ID    0x74
#define driverLeftBottom_ID  0x77
#define driverRightBottom_ID 0x74

#define PixelsGrouped 72  // for combining the brightness data of 72 pixels
#define PixelsTotal   144 // total number of pixels per driver




/**************************************************************************/
/*!
    @brief Constructor for nixiePanel
*/
/**************************************************************************/
class nixiePanel
{
public:
  nixiePanel(void);
  bool begin(void);
  void updateScreen(void);

  Adafruit_GFX myGFX  = Adafruit_GFX();
protected:

private:
  TwoWire DefaultLine = TwoWire(0);
  TwoWire AlteredLine = TwoWire(1);

  is31fl3731 driverLeftTop      = is31fl3731();
  is31fl3731 driverRightTop     = is31fl3731();
  is31fl3731 driverLeftBottom   = is31fl3731();
  is31fl3731 driverRightBottom  = is31fl3731();

  

};
#endif