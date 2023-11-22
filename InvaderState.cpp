#include "InvaderState.h"

InvaderState::InvaderState(float x, float y, int w, int h)
  : x(x), y(y), width(w), height(h),
    basePeriod(random(MOOD_PERIOD_MIN, MOOD_PERIOD_MAX)),
    modPeriod(random(MOOD_PERIOD_MIN, MOOD_PERIOD_MAX)),  // Different period for modulation
    phase(TWO_PI * random(100) / 100.0),
    amplitude(0.3 + random(70) / 100.0), decisionRate(random(DECISION_RATE_MIN, DECISION_RATE_MAX)) {}

void InvaderState::setPosition(float x, float y) {
  this->x = x;
  this->y = y;
}

float InvaderState::getMood() const {
  float result = 0.0;
  if (alive == true) {
    unsigned long currentTime = millis() % max(int(basePeriod), int(modPeriod));
    // Calculate the modulation factor
    float modFactor = amplitude * sin(TWO_PI * currentTime / modPeriod + phase);
    // Modulate the base period with the modulation factor
    float effectivePeriod = basePeriod * (1 + modFactor);
    result = sin(TWO_PI * currentTime / effectivePeriod);
  }
  return result;
}

bool InvaderState::moodEnteredZone(float zoneMin, float zoneMax) {
  float currentMood = getMood();

  // Check if mood just entered the zone
  bool enteredZone = (currentMood >= zoneMin && currentMood <= zoneMax) && !(prevMood >= zoneMin && prevMood <= zoneMax);

  // Update previous mood value
  prevMood = currentMood;

  return enteredZone;
}

void InvaderState::updateBehaviour() {
  float mood = getMood();
  if (mood > friendlyThresh[0] && mood < friendlyThresh[1]) {
    behavior = MOOD_FRIENDLY;
  } else if (mood > aggroThresh[0] && mood < aggroThresh[1]) {
    behavior = MOOD_AGGRO;
  } else {
    behavior = MOOD_IDLE;
  }
}

float InvaderState::getX() const {
  return x;
}

float InvaderState::getY() const {
  return y;
}

float InvaderState::getSpeed() {
  return speed;
}

void InvaderState::setSpeed(float s) {
  speed = s;
}

float InvaderState::getInertia() {
  return inertia;
}

void InvaderState::setInertia(float i) {
  inertia = i;
}

bool InvaderState::isAlive() {
  return alive;
}

bool InvaderState::kill() {
  alive = false;
}
