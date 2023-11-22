#ifndef INVADERSTATE_H
#define INVADERSTATE_H

#include <Arduino.h>  // Needed for millis and sin functions
#include "constants.h"

class InvaderState {
public:
  InvaderState(float x, float y, int w, int h);
  void setPosition(float x, float y);
  float getMood() const;
  float getX() const;
  float getY() const;
  bool moodEnteredZone(float zoneMin, float zoneMax);
  float getSpeed();
  void setSpeed(float s);
  float getInertia();
  void setInertia(float i);
  void updateBehaviour();
  int width;
  int height;
  int behavior;
  int decisionRate;
  float idleThresh[2] = { -0.5, 0.5 };
  float aggroThresh[2] = { -1.0, -0.5 };
  float friendlyThresh[2] = { 0.5, 1 };
  bool isAlive();
  bool kill();
  bool reincarnate(InvaderState* states[]);
  int killCount = 0;


private:
  bool alive = true;
  float x, y;
  float basePeriod;  // Base period for the primary sine wave
  float modPeriod;   // Period for the modulating sine wave
  float phase;
  float amplitude;
  float prevMood = 0.0;
  float speed = 0.8;
  float inertia = 0.2;
};

#endif  // INVADERSTATE_H
