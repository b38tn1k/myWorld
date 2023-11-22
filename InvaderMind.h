#ifndef INVADERMIND_H
#define INVADERMIND_H

#include <Arduino.h>
#include "InvaderState.h"

class InvaderMind {
private:
    float direction;
    float oldDirection;
public:
    float weights[5];
    InvaderMind();
    void randomlyChooseDirection();
    void move(InvaderState &s);
    void chooseNewDirection(int id, int numInvaders, InvaderState* states[]);
};

#endif // INVADERMIND_H
