// display
#include "SPI.h"
#include "Arduino_HWSPI.h"
#include "Arduino_GFX.h"
#include "Arduino_ST7735.h"
Arduino_DataBus *bus = new Arduino_HWSPI(9 /* DC */, 8 /* CS */);
Arduino_GFX *gfx = new Arduino_ST7735(bus, 10 /* RST */, 3 /* rotation */, true /* IPS */, 80 /* width */, 160 /* height */, 26 /* col offset 1 */, 1 /* row offset 1 */, 26 /* col offset 2 */, 1 /* row offset 2 */);

#include <Encoder.h>
Encoder myEnc(2, 3);

// include the Servo library
#include <Servo.h>
Servo myServo;  // create a servo object

void setup() {
  gfx->begin();
  gfx->fillScreen(BLACK);
  gfx->setTextColor(WHITE, BLACK);
  gfx->setTextSize(8);

  myServo.attach(5);
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition < 0) {
    newPosition = 0;
    myEnc.write(0);
  }
  if (newPosition > 180) {
    newPosition = 180;
    myEnc.write(180);
  }
  if (newPosition != oldPosition) {
    gfx->setCursor(0, 0);
    gfx->print(newPosition);
    gfx->print("  ");

    // set the servo position
    myServo.write(newPosition);

    oldPosition = newPosition;
  }
}
