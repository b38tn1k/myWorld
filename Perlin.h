#ifndef Perlin_h
#define Perlin_h

#include "Arduino.h"

struct Vec2 {
    float x, y;
};

class Perlin {
private:
    Vec2 **gradients;
    int gridWidth;
    int gridHeight;

    float lerp(float a, float b, float t) const;
    float dotGridGradient(int ix, int iy, float x, float y) const;
    void initializeGradients();

public:
    Perlin(int width, int height);
    ~Perlin();
    float noise(float x, float y) const;
};

#endif
