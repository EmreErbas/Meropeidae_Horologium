#ifndef _HAL_NIXIEPANEL_H_
#define _HAL_NIXIEPANEL_H_

#include "is31fl3731.h"  
/**************************************************************************/
/*!
    @brief Constructor for IS31FL3731
*/
/**************************************************************************/
class nixiePanel
{
public:
  nixiePanel();
  bool begin(void);
  void demoShow(void);
  
  TwoWire DefaultLine = TwoWire(0);
  TwoWire AlteredLine = TwoWire(1);



  is31fl3731 ledmatrix1 = is31fl3731();
  is31fl3731 ledmatrix2 = is31fl3731();
  is31fl3731 ledmatrix3 = is31fl3731();
  is31fl3731 ledmatrix4 = is31fl3731();


protected:

private:

};
#endif
