#include <sys/_stdint.h>
#include "Invader.h"
#define IDLE 0
#define FRIENDLY 1
#define AGGRO 2

uint16_t moodRing[3] = {0xAFF5, 0xAD7F,  0xFD77};

uint16_t rColor() {
  uint8_t red = random(8, 32);
  uint8_t green = random(8, 64);
  uint8_t blue = random(8, 32);
  return (red << 11) | (green << 5) | blue;
}

Invader::Invader(int n) {
  body = new InvaderBody();
  invColor = rColor();
  state = new InvaderState(random(20, GEO_DISPLAY_WIDTH- 20), random(20, GEO_DISPLAY_HEIGHT-20), body->width, body->height);
  mind = new InvaderMind(n);
}

void Invader::draw(GigaDisplay_GFX& display) {
  int drawX = state->getX() - int(body->width / 2);
  int drawY = state->getY() - int(body->height / 2);
  display.drawBitmap(drawX, drawY, body->getBufferCopy(), body->width, body->height, invColor, COL_BLACK);
}

void Invader::log() {
  Serial.println(state->getMood());
}

void Invader::updateState(int id, int numInvaders, InvaderState* states[]) {
  updateBehaviour();
  if (state->moodEnteredZone(-0.5, 0.5) == true) {
    mind->chooseNewDirection(id, numInvaders, states);
  }
  // mind->chooseNewDirection(id, numInvaders, states);
  mind->move(*state);
  invColor = moodRing[behavior];
}

void Invader::updateBehaviour() {
  float mood = state->getMood();
  

  if (mood > friendlyThresh[0] && mood < friendlyThresh[1]) {
    behavior = FRIENDLY;
  } else if (mood > aggroThresh[0] && mood < aggroThresh[1]) {
    behavior = AGGRO;
  } else {
    behavior = IDLE;
  }

}

InvaderState& Invader::getState() {
  return *state;
}