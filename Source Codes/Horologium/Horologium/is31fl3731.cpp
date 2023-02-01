#include "is31fl3731.h"


/**************************************************************************/
/*!
    @brief Constructor for is31fl3731
*/
/**************************************************************************/

is31fl3731::is31fl3731(void)
{}

/**************************************************************************/
/*!
    @brief Initialize hardware and clear display
    @param addr The I2C address we expect to find the chip at
    @param theWire The TwoWire I2C bus device to use, defaults to &Wire
    @returns True on success, false if chip isnt found
*/
/**************************************************************************/
bool is31fl3731::begin(uint8_t addr, TwoWire *theWire) 
{
  if (_i2c_dev) 
  {
    delete _i2c_dev;
  }
  _i2c_dev = new Adafruit_I2CDevice(addr, theWire);

  if (!_i2c_dev->begin()) 
  {
    return false;
  }

  _i2c_dev->setSpeed(400000);

  // picture mode
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG, ISSI_REG_CONFIG_PICTUREMODE);
  
  _frame = 0;
  displayFrame(_frame);

  return true;
}

void is31fl3731::softReset(void) 
{
  // shutdown
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x00);
  delay(10);
  // out of shutdown
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0x01);

  // all LEDs on & 0 PWM
  clear(); // set each led to 0 PWM

  for (uint8_t f = 0; f < 8; f++) 
  {
    for (uint8_t i = 0; i <= 0x11; i++)
    {
      writeRegister8(f, i, 0xff); // each 8 LEDs on
    }
  }

  _frame = 0;
  displayFrame(_frame);
}


void is31fl3731::end(void) 
{
  _i2c_dev->end();
}

/**************************************************************************/
/*!
    @brief Sets all LEDs on & 0 PWM for current frame.
*/
/**************************************************************************/
void is31fl3731::clear(void) 
{
  uint8_t erasebuf[1 + 72];
   
  selectBank(_frame);
 
  memset(erasebuf, 0, 1 + 72);
  
  erasebuf[0] = 0x24;
  _i2c_dev->write(erasebuf, 1 + 72);

  erasebuf[0] = 0x24 + 72;
  _i2c_dev->write(erasebuf, 1 + 72);
}

/**************************************************************************/
/*!
    @brief Low level accesssor - sets a 8-bit PWM pixel value to a bank location
    does not handle rotation, x/y or any rearrangements!
    @param lednum The offset into the bank that corresponds to the LED
    @param bank The bank/frame we will set the data in
    @param pwm brightnes, from 0 (off) to 255 (max on)
*/
/**************************************************************************/
void is31fl3731::setLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank) 
{
  writeRegister8(bank, 0x24 + lednum, pwm);
}

/**************************************************************************/
/*!
    @brief Set's this object's frame tracker (does not talk to the chip)
    @param frame Ranges from 0 - 7 for the 8 frames
*/
/**************************************************************************/
void is31fl3731::setFrame(uint8_t frame) { _frame = frame; }

/**************************************************************************/
/*!
    @brief Have the chip set the display to the contents of a frame
    @param frame Ranges from 0 - 7 for the 8 frames
*/
/**************************************************************************/
void is31fl3731::displayFrame(uint8_t frame) {
  if (frame > 7)
    frame = 0;
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_PICTUREFRAME, frame);
}

/**************************************************************************/
/*!
    @brief Switch to a given bank in the chip memory for future reads
    @param bank The IS31 bank to switch to
    @returns False if I2C command failed to be ack'd
*/
/**************************************************************************/
bool is31fl3731::selectBank(uint8_t bank) {
  uint8_t cmd[2] = {ISSI_COMMANDREGISTER, bank};
  return _i2c_dev->write(cmd, 2);
}

/**************************************************************************/
/*!
    @brief Write one byte to a register located in a given bank
    @param bank The IS31 bank to write the register location
    @param reg the offset into the bank to write
    @param data The byte value
    @returns False if I2C command failed to be ack'd
*/
/**************************************************************************/
bool is31fl3731::writeRegister8(uint8_t bank, uint8_t reg,
                                         uint8_t data) {
  selectBank(bank);

  uint8_t cmd[2] = {reg, data};
  return _i2c_dev->write(cmd, 2);
}

/**************************************************************************/
/*!
    @brief  Read one byte from a register located in a given bank
    @param   bank The IS31 bank to read the register location
    @param   reg the offset into the bank to read
    @return 1 byte value
*/
/**************************************************************************/
uint8_t is31fl3731::readRegister8(uint8_t bank, uint8_t reg) {
  uint8_t val = 0xFF;

  selectBank(bank);

  _i2c_dev->write_then_read(&reg, 1, &val, 1);

  return val;
}
