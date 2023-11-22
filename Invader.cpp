#include <sys/_stdint.h>
#include "Invader.h"

uint16_t moodRing[3] = { 0xAFF5, 0xAD7F, 0xFD77 };

uint16_t rColor() {
  uint8_t red = random(8, 32);
  uint8_t green = random(8, 64);
  uint8_t blue = random(8, 32);
  return (red << 11) | (green << 5) | blue;
}

Invader::Invader() {
  body = new InvaderBody();
  invColor = rColor();
  state = new InvaderState(random(20, GEO_DISPLAY_WIDTH - 20), random(20, GEO_DISPLAY_HEIGHT - 20), body->width, body->height);
  mind = new InvaderMind();
}

void Invader::draw(GigaDisplay_GFX& display) {
  if (state->isAlive() == true) {
    int drawX = state->getX() - int(body->width / 2);
    int drawY = state->getY() - int(body->height / 2);
    display.drawBitmap(drawX, drawY, body->getBufferCopy(), body->width, body->height, invColor, COL_BLACK);
  }
}

void Invader::log() {
  Serial.println(state->getMood());
}

int Invader::checkCollisionGetId(int id, int numInvaders, InvaderState* states[]) {
  for (int i = 0; i < numInvaders; ++i) {
    if (i != id) {  // Skip checking collision with itself
      float distance = calculateDistance(states[id], states[i]);
      if (distance < GEO_INV_COLLISION_THRESH) {
        return i;
      }
    }
  }
  return -1;
}

float Invader::calculateDistance(const InvaderState* state1, const InvaderState* state2) {
  float dx = state1->getX() - state2->getX();
  float dy = state1->getY() - state2->getY();
  return sqrt(dx * dx + dy * dy);
}

void Invader::incrementKillCount() {
  state->killCount += 1;
}

int Invader::getKillCount() {
  return state->killCount;
}

int Invader::updateState(int id, int numInvaders, InvaderState* states[]) {
  int collided = -1;
  if (state->isAlive() == true) {
    state->updateBehaviour();
    counter += 1;
    if (counter % state->decisionRate == 0) {
      mind->chooseNewDirection(id, numInvaders, states);
    }
    mind->move(*state);
    invColor = moodRing[state->behavior];
    collided = checkCollisionGetId(id, numInvaders, states);
  } else {
    state->setPosition(0, 0);
  }
  return collided;
}

int Invader::checkCurrentBehavior() {
  return state->behavior;
}

void Invader::mutateMind(Invader* p1, Invader* p2){
  for (int i = 0; i < 5; i++) {
    if (random(2) >= 1) {
      mind->weights[i] = p1->mind->weights[i];
    } else {
      mind->weights[i] = p2->mind->weights[i];
    }
  }
}


void Invader::mutateBody(Invader* p1, Invader* p2){

}

void Invader::kill() {
  counter = 0;
  state->kill();
}

InvaderState& Invader::getState() {
  return *state;
}