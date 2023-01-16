#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

// If you're using the full breakout...
Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();
// If you're using the FeatherWing version
//Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();


// The lookup table to make the brightness changes be more visible
uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
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
}
/* Drawing
You can then draw to the display. Note that since we write directly 
to the driver RAM, any pixels 'drawn' will appear immediately.

You can start with drawPixel(x, y, brightness) where x ranges between 
0 and 15 inclusive, and y ranges between 0 and 8 inclusive. Brightness 
is the PWM of the LED, 0 is off, and 255 is all the way on.

This loop will light up every LED in increasing brightness: */
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(200);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  // animate over all the pixels, and set the brightness from the sweep table
  for (uint8_t incr = 0; incr < 24; incr++)
    for (uint8_t x = 0; x < 16; x++)
      for (uint8_t y = 0; y < 9; y++)
        ledmatrix.drawPixel(x, y, sweep[(x+y+incr)%24]);
  delay(200);
   Serial.println("IS31 not found");
}