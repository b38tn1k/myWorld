#include "constants.h"
#include "Arduino_GigaDisplay_GFX.h"
#include "Invader.h"
#include "InvaderState.h"
#include "Landscape.h"

GigaDisplay_GFX display;
const int numInvaders = 7;

Invader* invaders[numInvaders];
InvaderState* states[numInvaders];
Landscape *ls;
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
  ls = new Landscape();
  
  // Initialize the invaders
  for (int i = 0; i < numInvaders; ++i) {
    invaders[i] = new Invader(numInvaders);
  }
}

void loop() {
  update();
  draw();
}

void update() {
  for (int i = 0; i < numInvaders; ++i) {
    states[i] = &invaders[i]->getState();
  }
  for (int i = 0; i < numInvaders; ++i) {
    invaders[i]->updateState(i, numInvaders, states);
  }
}

void draw() {
  // display.drawBitmap(0, 0, ls->getBufferCopy(), ls->width, ls->height, COL_DARK_GREY, COL_BLACK);
  for (int i = 0; i < numInvaders; ++i) {
    invaders[i]->draw(display);
  }
}
