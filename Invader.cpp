#include "Invader.h"

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

void Invader::updateState(int id, int numInvaders, InvaderState* states[]) {
  if (state->moodEnteredZone(0.0, 1.0) == true) {
    mind->chooseNewDirection();
    invColor = rColor();
  }
  mind->move(*state);
}

InvaderState& Invader::getState() {
  return *state;
}