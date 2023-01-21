#ifndef _HAL_NIXIEPANEL_H_
#define _HAL_NIXIEPANEL_H_

#include "is31fl3731.h"  
#include "Adafruit_GFX.h"

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


protected:

private:
  TwoWire DefaultLine = TwoWire(0);
  TwoWire AlteredLine = TwoWire(1);

  is31fl3731 driverLeftTop      = is31fl3731();
  is31fl3731 driverRightTop     = is31fl3731();
  is31fl3731 driverLeftBottom   = is31fl3731();
  is31fl3731 driverRightBottom  = is31fl3731();

  Adafruit_GFX myGFX  = Adafruit_GFX(36, 16);


};
#endif