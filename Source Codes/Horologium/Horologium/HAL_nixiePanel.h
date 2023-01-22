#ifndef _HAL_NIXIEPANEL_H_
#define _HAL_NIXIEPANEL_H_

#include "is31fl3731.h"  
#include "Adafruit_GFX.h"

#define WIDTH  36       ///< This is the 'raw' display width  - never changes
#define HEIGHT 16       ///< This is the 'raw' display height - never changes

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
  void demoShow(void);
  void demoFont(void);

protected:

private:
  TwoWire DefaultLine = TwoWire(0);
  TwoWire AlteredLine = TwoWire(1);

  is31fl3731 driverLeftTop      = is31fl3731();
  is31fl3731 driverRightTop     = is31fl3731();
  is31fl3731 driverLeftBottom   = is31fl3731();
  is31fl3731 driverRightBottom  = is31fl3731();

  Adafruit_GFX myGFX  = Adafruit_GFX();
  

};
#endif