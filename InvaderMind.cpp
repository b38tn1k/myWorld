#include "InvaderMind.h"

float lerp(float start, float end, float t) {
    return start + t * (end - start);
}

InvaderMind::InvaderMind(int n) : direction(random(360) * DEG_TO_RAD), oldDirection(random(360) * DEG_TO_RAD) {}

void InvaderMind::chooseNewDirection() {
    oldDirection = direction;
    direction = random(3600) * DEG_TO_RAD; // Random direction in radians
}

void InvaderMind::move(InvaderState &state) {
    // Retrieve current position
    float x = state.getX();
    float y = state.getY();
    float step = state.getSpeed();

    // Predict next position
    float nextX = x + step * cos(oldDirection);
    float nextY = y + step * sin(oldDirection);

    // Boundary checks
    bool outOfBounds = false;
    if (nextX < state.width / 2) {
        nextX = state.width / 2 + 1; // Nudge towards the center
        outOfBounds = true;
    } else if (nextX > GEO_DISPLAY_WIDTH - state.width / 2) {
        nextX = GEO_DISPLAY_WIDTH - state.width / 2 - 1;
        outOfBounds = true;
    }
    if (nextY < state.height / 2) {
        nextY = state.height / 2 + 1;
        outOfBounds = true;
    } else if (nextY > GEO_DISPLAY_HEIGHT - state.height / 2) {
        nextY = GEO_DISPLAY_HEIGHT - state.height / 2 - 1;
        outOfBounds = true;
    }

    // If out of bounds, change direction and adjust position
    if (outOfBounds) {
        chooseNewDirection();
        x = nextX;
        y = nextY;
    } else {
        // Smoothly transition to the new direction
        float smoothDirection = lerp(oldDirection, direction, state.getInertia());
        x += step * cos(smoothDirection);
        y += step * sin(smoothDirection);

        // Update oldDirection for next iteration
        oldDirection = smoothDirection;
    }

    // Update position
    state.setPosition(x, y);
}


