#include "InvaderBody.h"
#include "InvaderState.h"
#include "InvaderMind.h"

class Invader {
private:
  InvaderState* state;
  InvaderBody* body;
  InvaderMind* mind;
  uint16_t invColor = COL_WHITE;
  void updateBehaviour();
  float idleThresh[2] = {-0.5, 0.5};
  float aggroThresh[2] = {-1.0, -0.5};
  float friendlyThresh[2] = {0.5, 1};
  uint8_t behavior = 0;
public:
  Invader(int n);
   void updateState(int id, int numInvaders, InvaderState* states[]);
  InvaderState& getState();
  void draw(GigaDisplay_GFX & display);
  void log();
};
