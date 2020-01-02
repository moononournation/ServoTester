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
  gfx->setTextSize(2);
  gfx->setCursor(0, 0);
  gfx->setTextColor(WHITE, RED);
  gfx->print("Servo ");
  gfx->setTextColor(WHITE, GREEN);
  gfx->print("Tester ");
  gfx->setCursor(0, 24);
  gfx->setTextColor(CYAN, BLACK);
  gfx->println("Pulse\nWidth");
  gfx->setCursor(0, 64);
  gfx->setTextColor(BLUE, BLACK);
  gfx->println("Angle");

  myServo.attach(5);
  myEnc.write(DEFAULT_PULSE_WIDTH);
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition < MIN_PULSE_WIDTH) {
    newPosition = MIN_PULSE_WIDTH;
    myEnc.write(MIN_PULSE_WIDTH);
  }
  if (newPosition > MAX_PULSE_WIDTH) {
    newPosition = MAX_PULSE_WIDTH;
    myEnc.write(MAX_PULSE_WIDTH);
  }
  if (newPosition != oldPosition) {
    gfx->setTextSize(4);
    gfx->setTextColor(WHITE, BLACK);
    gfx->setCursor(64, 24);
    if (newPosition < 1000) {
      gfx->print(" ");
    }
    gfx->print(newPosition);

    int angle = map(newPosition, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, 0, 180);
    gfx->setTextSize(2);
    gfx->setTextColor(WHITE, BLACK);
    gfx->setCursor(64, 64);
    gfx->print(angle);
    gfx->print("  ");

    // set the servo position
    myServo.write(newPosition);

    oldPosition = newPosition;
  }
}
