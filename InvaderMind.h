#ifndef INVADERMIND_H
#define INVADERMIND_H

#include <Arduino.h>
#include "InvaderState.h"

class InvaderMind {
private:
    float direction;
    float oldDirection;
    float weights[5];

public:
    InvaderMind(int n);
    void randomlyChooseDirection();
    void move(InvaderState &s);
    void chooseNewDirection(int id, int numInvaders, InvaderState* states[]);
};

#endif // INVADERMIND_H
