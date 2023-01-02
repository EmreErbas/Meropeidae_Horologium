# How to Drive IS31FL3731
## IS31FL3731
### GENERAL DESCRIPTION

The [IS31FL3731](https://www.lumissil.com/assets/pdf/core/IS31FL3731_DS.pdf) is a compact LED driver for 144 single LEDs. The device can be programmed via an I2C compatible interface. The IS31FL3731 offers two blocks each driving 72 LEDs with 1/9 cycle rate. The required lines to drive all 144 LEDs are reduced to 18 by using the cross-plexing feature optimizing space on the PCB. Additionally each of the 144 LEDs can be dimmed individually with 8-bit allowing 256 steps of linear dimming.

To reduce CPU usage up to 8 frames can be stored with individual time delays between frames to play small animations automatically. LED frames can be modulated with audio signal.

IS31FL3731 is available in QFN-28 (4mm × 4mm) and SSOP-28 package. It operates from 2.7V to 5.5V over the temperature range of -40°C to +85°C.

### FEATURES
* Supply voltage range: 2.7V to 5.5V 
* 400kHz I2C-compatible interface
* 144 LEDs in dot matrix
* Individual blink control
* 8 frames memory for animations
* Picture mode and animation mode
* Auto intensity breathing during the switching of different frames
* LED frames displayed can be modulated with audio signal intensity
* LED light intensity can be modulated with audio signal intensity
* QFN-28 (4mm × 4mm) and SSOP-28 package


Typical Application Circuit is:
<img src="https://github.com/EmreErbas/Nixie/blob/main/Documents/Notes/Pictures/IS31FL3731_TAC.png" width="1000" />

The circuit that the Nixie-Panel project uses is: 
<img src="https://github.com/EmreErbas/Nixie/blob/main/Documents/Notes/Pictures/IS31FL3731_Circuit.png" width="1000" />

under this hierarchical page:
<img src="https://github.com/EmreErbas/Nixie/blob/main/Documents/Notes/Pictures/IS31FL3731_Block.png" width="1000" />

## Driving the IC
Adafruit has a library for this IC. [Here](https://learn.adafruit.com/i31fl3731-16x9-charliplexed-pwm-led-driver/overview) is the link.
