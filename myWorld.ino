#include "constants.h"
#include "Arduino_GigaDisplay_GFX.h"
#include "InvaderBody.h"

GigaDisplay_GFX display;
InvaderBody inv = InvaderBody();

unsigned long previousMillis = -1000;
const long interval = 1000;

void setup() {
  // Serial.begin(115200);
  // Serial.println("Start Up");
  display.begin();
  display.setRotation(1);
}

void loop() {
  
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    display.fillScreen(COL_BLACK);
    previousMillis = currentMillis;
  }
  display.drawBitmap(150, 240, inv.cnv.getBuffer(), inv.cnv.width(), inv.cnv.height(), COL_YELLOW, COL_BLUE);
}
