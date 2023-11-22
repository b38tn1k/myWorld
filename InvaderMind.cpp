#include "InvaderMind.h"

float lerp(float start, float end, float t) {
  return start + t * (end - start);
}

InvaderMind::InvaderMind()
  : direction(random(360) * DEG_TO_RAD), oldDirection(random(360) * DEG_TO_RAD) {
  for (int i = 0; i < 5; i++) {
    weights[i] = (TWO_PI * 2 * (random(10000) / 10000.0)) - TWO_PI;
  }
}

void InvaderMind::randomlyChooseDirection() {
  oldDirection = direction;
  direction = random(3600) * DEG_TO_RAD;  // Random direction in radians
}

void InvaderMind::chooseNewDirection(int id, int numInvaders, InvaderState* states[]) {
  oldDirection = direction;

  // Initialize an array to store the calculated values
  float calculatedValues[numInvaders - 1][5];  // 5 values for each state

  float currentX = states[id]->getX();
  float currentY = states[id]->getY();

  int index = 0;
  for (int i = 0; i < numInvaders; i++) {
    if (i != id) {  // Skip the current invader's state
      float x = states[i]->getX();
      float y = states[i]->getY();

      // Calculate angle and hypotenuse
      float deltaX = x - currentX;
      float deltaY = y - currentY;
      float angle = atan2(deltaY, deltaX);  // Angle in radians
      float hypotenuse = sqrt(deltaX * deltaX + deltaY * deltaY);

      // Store the values in the array
      calculatedValues[index][0] = states[i]->getMood();
      calculatedValues[index][1] = states[i]->getSpeed();
      calculatedValues[index][2] = states[i]->getInertia();
      calculatedValues[index][3] = angle;
      calculatedValues[index][4] = hypotenuse;

      index++;
    }
  }

  float directionSum = 0;
  for (int i = 0; i < numInvaders - 1; i++) {
    float dotProduct = 0;
    for (int j = 0; j < 5; j++) {
      dotProduct += calculatedValues[i][j] * weights[j];
    }
    directionSum += dotProduct;
  }

  direction = directionSum / (numInvaders - 1);

  // // just do it runs for now:
  // randomlyChooseDirection();
}

void InvaderMind::move(InvaderState& state) {
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
    nextX = state.width / 2 + 1;  // Nudge towards the center
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
    randomlyChooseDirection();
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
