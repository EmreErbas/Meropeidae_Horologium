#ifndef _IS31FL3731_H_
#define _IS31FL3731_H_

#include <Arduino.h>
#include "Adafruit_I2CDevice.h"

#define ISSI_REG_CONFIG 0x00
#define ISSI_REG_CONFIG_PICTUREMODE 0x00
#define ISSI_REG_CONFIG_AUTOPLAYMODE 0x08
#define ISSI_REG_CONFIG_AUDIOPLAYMODE 0x18

#define ISSI_CONF_PICTUREMODE 0x00
#define ISSI_CONF_AUTOFRAMEMODE 0x04
#define ISSI_CONF_AUDIOMODE 0x08

#define ISSI_REG_PICTUREFRAME 0x01

#define ISSI_REG_SHUTDOWN 0x0A
#define ISSI_REG_AUDIOSYNC 0x06

#define ISSI_COMMANDREGISTER 0xFD
#define ISSI_BANK_FUNCTIONREG 0x0B // helpfully called 'page nine'

#define ISSI_PIXEL_StartAddress 0x24

/**************************************************************************/
/*!
    @brief Constructor for IS31FL3731
*/
/**************************************************************************/
class is31fl3731
{
public:
  is31fl3731(void);
  bool begin(uint8_t addr, TwoWire *theWire = &Wire);
  bool selectBank(uint8_t bank);
  void softReset(void);
  void end(void);
  void clear(void);

  void setLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank = 0);
  void setFrame(uint8_t b);
  void displayFrame(uint8_t frame);
  
  Adafruit_I2CDevice *_i2c_dev = NULL;
  
protected:
  bool writeRegister8(uint8_t bank, uint8_t reg, uint8_t data);
  uint8_t readRegister8(uint8_t bank, uint8_t reg);
  uint8_t _frame; ///< The frame (of 8) we are currently addressing

private:

};
#endif

