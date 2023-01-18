#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
Adafruit_IS31FL3731 ledmatrix2 = Adafruit_IS31FL3731();
Adafruit_IS31FL3731 ledmatrix3 = Adafruit_IS31FL3731();
Adafruit_IS31FL3731 ledmatrix4 = Adafruit_IS31FL3731();

// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();


// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 29, 32, 35, 38, 41, 44,
                  47, 44, 41, 38, 35, 32, 29, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 7, 6, 5, 4, 3, 2, 1};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println("ISSI swirl test");


// call begin(address) to initialize the driver. 
// Begin() will return false if the matrix was not found,
//                 and true if initialization worked out
  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(60);                      // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(60);                      // wait for a second
  }
  Serial.println("IS31 found!");
  ledmatrix2.begin(0x75);
  ledmatrix3.begin(0x76);  
  ledmatrix4.begin(0x77);
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

  
  for (uint8_t incr = 0; incr < 48; incr+=2)
  {
    for (uint8_t x = 0; x < 16; x++)
    {
      for (uint8_t y = 0; y < 9; y++)
      {
        ledmatrix.setLEDPWM (x + (y << 4), sweep[(x + y + incr + 2) % 48]);
        ledmatrix2.setLEDPWM(x + (y << 4), sweep[(x + y + incr) % 48]);    
        ledmatrix3.setLEDPWM(x + (y << 4), sweep[(x + y + incr) % 48]); 
        ledmatrix4.setLEDPWM(x + (y << 4), sweep[(x + y + incr) % 48]); 
      }
    }
  }
  
}