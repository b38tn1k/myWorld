#include "constants.h"
#include "Arduino_GigaDisplay_GFX.h"
#include "InvaderBody.h"

GigaDisplay_GFX display;
InvaderBody inv = InvaderBody();

unsigned long previousMillis = -1000;
const long interval = 50;

void setup() {
  // Serial.begin(115200);
  // Serial.println("Start Up");
  display.begin();
  display.fillScreen(COL_BLACK);
  display.setRotation(1);
}


int x = 400;
int y = 240;

void loop() {
  // unsigned long currentMillis = millis();
  // if (currentMillis - previousMillis >= interval) {
  //   // display.fillScreen(COL_BLACK);
  //   previousMillis = currentMillis;
  // }
  y = int(240.0 + 50.0 * sin(millis() / 1000.0));
  display.drawBitmap(x, y, inv.bufferCopy, inv.cnv.width(), inv.cnv.height(), COL_YELLOW, COL_BLACK);
}
