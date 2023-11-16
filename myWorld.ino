#include "constants.h"
#include "Arduino_GigaDisplay_GFX.h"
#include "InvaderBody.h"
#include "Landscape.h"

GigaDisplay_GFX display;
const int numInvaders = 5;
const uint16_t colorArray[] = {COL_CYAN, COL_RED, COL_BLUE, COL_GREEN, COL_MAGENTA, COL_WHITE, COL_BLACK, COL_YELLOW};
InvaderBody* invaders[numInvaders];
Landscape ls;
int spacing = GEO_DISPLAY_WIDTH / (numInvaders + 1);

unsigned long previousMillis = -1000;
const long interval = 50;

void setup() {
  Serial.begin(115200);
  int noise = 0;
  for (int i = 0; i < 1000; i++) {
    noise += analogRead(0) + analogRead(1) + analogRead(3) + analogRead(4);
  }
  randomSeed(noise);
  display.begin();
  display.fillScreen(COL_BLACK);
  display.setRotation(1);
  ls = Landscape();
  
  // Initialize the invaders
  for (int i = 0; i < numInvaders; ++i) {
    invaders[i] = new InvaderBody();
    invaders[i]->logSourceGrid();
  }

  for (int i = 0; i < numInvaders; ++i) {
    invaders[i]->logSourceGrid();
  }
}

void loop() {
  draw();
}

void draw() {
  for (int i = 0; i < numInvaders; ++i) {
    int x = spacing * (i + 1);
    int y = 240 + 50 * sin((millis() / 1000.0) + (x * 0.01)); // Phase depends on x position
    display.drawBitmap(x - int(invaders[i]->width/2), y - int(invaders[i]->height/2), invaders[i]->getBufferCopy(), invaders[i]->width, invaders[i]->height, colorArray[i], COL_BLACK);
  }
}
