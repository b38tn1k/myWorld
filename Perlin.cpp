#include "Perlin.h"

Perlin::Perlin(int width, int height) : gridWidth(width), gridHeight(height) {
    gradients = new Vec2*[gridWidth];
    for (int i = 0; i < gridWidth; ++i) {
        gradients[i] = new Vec2[gridHeight];
    }
    initializeGradients();
}

Perlin::~Perlin() {
    for (int i = 0; i < gridWidth; ++i) {
        delete[] gradients[i];
    }
    delete[] gradients;
}

void Perlin::initializeGradients() {
    for (int i = 0; i < gridWidth; i++) {
        for (int j = 0; j < gridHeight; j++) {
            float angle = random(360) * PI / 180.0;
            gradients[i][j] = {cos(angle), sin(angle)};
        }
    }
}

float Perlin::lerp(float a, float b, float t) const {
    return a + t * (b - a);
}

float Perlin::dotGridGradient(int ix, int iy, float x, float y) const {
    float dx = x - (float)ix;
    float dy = y - (float)iy;
    Vec2 gradient = gradients[ix][iy];
    return (dx * gradient.x + dy * gradient.y);
}

float Perlin::noise(float x, float y) const {
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0, n1, ix0, ix1;
    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = lerp(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = lerp(n0, n1, sx);
    // Serial.print(ix0);
    // Serial.print(" ");
    // Serial.print(ix1);
    // Serial.print(" ");
    // Serial.print(sy);
    // Serial.println();
    return lerp(ix0, ix1, sy);
}
