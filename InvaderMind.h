#ifndef INVADERMIND_H
#define INVADERMIND_H

#include <Arduino.h>
#include "InvaderState.h"

class InvaderMind {
private:
    float direction;
    float oldDirection;

public:
    InvaderMind(int n);
    void chooseNewDirection();
    void move(InvaderState &s);
};

#endif // INVADERMIND_H
