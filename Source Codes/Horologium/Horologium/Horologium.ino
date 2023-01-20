#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
Adafruit_IS31FL3731 ledmatrix1 = Adafruit_IS31FL3731();
Adafruit_IS31FL3731 ledmatrix2 = Adafruit_IS31FL3731();
Adafruit_IS31FL3731 ledmatrix3 = Adafruit_IS31FL3731();
Adafruit_IS31FL3731 ledmatrix4 = Adafruit_IS31FL3731();

TwoWire DefaultLine = TwoWire(0);
TwoWire AlteredLine = TwoWire(1);

// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 29, 32, 35, 38, 41, 44,
                  47, 44, 41, 38, 35, 32, 29, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 7, 6, 5, 4, 3, 2, 1};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("ISSI swirl test");

// https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf#page=48
// https://github.com/EmreErbas/Meropeidae_Horologium/blob/main/Documents/Notes/03-How%20to%20program%20ESP32-S3.md
  DefaultLine.setPins(3, 4);
  AlteredLine.setPins(3, 5);
  
  ledmatrix1.begin(0x74, &DefaultLine);
  ledmatrix2.begin(0x77, &DefaultLine);
  ledmatrix1.hardClear();
  ledmatrix2.hardClear();
  ledmatrix1.end();
  ledmatrix2.end(); 

  ledmatrix3.begin(0x74, &AlteredLine);  
  ledmatrix4.begin(0x77, &AlteredLine);
  ledmatrix3.hardClear();
  ledmatrix4.hardClear();
  ledmatrix3.end();
  ledmatrix4.end(); 

// call begin(address) to initialize the driver. 
// Begin() will return false if the matrix was not found,
//                 and true if initialization worked out
//  ledmatrix1.begin(0x74, &DefaultLine);
//  ledmatrix2.begin(0x75, &DefaultLine);
//  ledmatrix3.begin(0x76, &AlteredLine);  
//  ledmatrix4.begin(0x77, &AlteredLine);
}
/* Drawing
You can then draw to the display. Note that since we write directly 
to the driver RAM, any pixels 'drawn' will appear immediately.

You can start with drawPixel(x, y, brightness) where x ranges between 
0 and 15 inclusive, and y ranges between 0 and 8 inclusive. Brightness 
is the PWM of the LED, 0 is off, and 255 is all the way on.

This loop will light up every LED in increasing brightness: */

void loop() {
  // animate over all the pixels, and set the brightness from the sweep table

  // activate the default clock line to reach the upper drivers

  ledmatrix1.begin(0x74, &DefaultLine);
  ledmatrix2.begin(0x77, &DefaultLine);
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {
        ledmatrix1.setLEDPWM(x + (y << 4), sweep[(x + y + incr + 2) % 48]);
      }
    }
  }
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {
        ledmatrix2.setLEDPWM(x + (y << 4), sweep[(x + y + incr) % 48]);    
      }
    }
  }
  ledmatrix1.end();
  ledmatrix2.end();

  ledmatrix3.begin(0x74, &AlteredLine);  
  ledmatrix4.begin(0x77, &AlteredLine);
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {  
        ledmatrix3.setLEDPWM(x + (y << 4), sweep[(x + y + incr + 2) % 48]); 
      }
    }
  }
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {  
        ledmatrix4.setLEDPWM(x + (y << 4), sweep[(x + y + incr) % 48]); 
      }
    }
  }
  ledmatrix3.end();
  ledmatrix4.end();
  
}