#include "InvaderBody.h"
#include "InvaderState.h"
#include "InvaderMind.h"

class Invader {
private:
  InvaderState* state;
  InvaderBody* body;
  InvaderMind* mind;
  uint16_t invColor = COL_WHITE;
  long counter = 0;
  int checkCollisionGetId(int id, int numInvaders, InvaderState* states[]);
  float calculateDistance(const InvaderState* state1, const InvaderState* state2);
public:
  int checkCurrentBehavior();
  Invader();
  int updateState(int id, int numInvaders, InvaderState* states[]);
  InvaderState& getState();
  void draw(GigaDisplay_GFX& display);
  void log();
  void kill();
  void incrementKillCount();
  int getKillCount();
  void mutateMind(Invader* p1, Invader* p2);
  void mutateBody(Invader* p1, Invader* p2);
};
