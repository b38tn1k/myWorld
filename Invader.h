#include "InvaderBody.h"
#include "InvaderState.h"
#include "InvaderMind.h"

class Invader {
private:
  InvaderState* state;
  InvaderBody* body;
  InvaderMind* mind;
  uint16_t invColor = COL_WHITE;
public:
  Invader(int n);
   void updateState(int id, int numInvaders, InvaderState* states[]);
  InvaderState& getState();
  void draw(GigaDisplay_GFX & display);
};
