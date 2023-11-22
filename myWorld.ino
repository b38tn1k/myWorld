#include "constants.h"
#include "Arduino_GigaDisplay_GFX.h"
#include "Invader.h"
#include "InvaderState.h"
#include "Landscape.h"

// Landscape *ls;
// ls = new Landscape();
// display.drawBitmap(0, 0, ls->getBufferCopy(), ls->width, ls->height, COL_DARK_GREY, COL_BLACK);

GigaDisplay_GFX display;

const int numInvaders = 7;
Invader* invaders[numInvaders];
InvaderState* states[numInvaders];
int spacing = GEO_DISPLAY_WIDTH / (numInvaders + 1);

unsigned long previousMillis = -1000;
const long interval = 50;

void setup() {
  Serial.begin(115200);
  // seed random
  int noise = 0;
  for (int i = 0; i < 1000; i++) {
    noise += analogRead(0) + analogRead(1) + analogRead(3) + analogRead(4);
  }
  randomSeed(noise);

  // display
  display.begin();
  display.fillScreen(COL_BLACK);
  display.setRotation(1);

  // Initialize the invaders
  for (int i = 0; i < numInvaders; ++i) {
    invaders[i] = new Invader();
  }
}

void loop() {
  update();
  draw();
}

void update() {
  bool someoneIsDead = false;
  for (int i = 0; i < numInvaders; ++i) {
    states[i] = &invaders[i]->getState();
    if (states[i]->isAlive() == false) {
      someoneIsDead = true;
    }
  }

  bool alreadyCollided = false;
  for (int i = 0; i < numInvaders; ++i) {
    int c = invaders[i]->updateState(i, numInvaders, states);
    if (alreadyCollided == false && c != -1) {
      int bi = invaders[i]->checkCurrentBehavior();
      int bc = invaders[c]->checkCurrentBehavior();
      if (bi == MOOD_AGGRO && bc != MOOD_AGGRO) {
        invaders[c]->kill();
        invaders[i]->incrementKillCount();
      } else if (bc == MOOD_AGGRO && bi == MOOD_AGGRO) {
        if (invaders[i]->getKillCount() >= invaders[c]->getKillCount()) {
          invaders[c]->kill();
          invaders[i]->incrementKillCount();
        }
      } else if (bi == MOOD_FRIENDLY && someoneIsDead == true && bc != MOOD_AGGRO) {
        for (int j = 0; j < numInvaders; ++j) {
          if (states[j]->isAlive() == false) {
            invaders[j] = new Invader();
            invaders[j]->mutateMind(invaders[i], invaders[c]);
            invaders[j]->mutateBody(invaders[i], invaders[c]);
          }
        }
      }
    }
  }
}

void draw() {
  for (int i = 0; i < numInvaders; ++i) {
    invaders[i]->draw(display);
  }
}
