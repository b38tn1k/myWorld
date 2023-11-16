// Invader.cpp
#include "InvaderBody.h"
#include "Arduino_GigaDisplay_GFX.h"
#include "constants.h"

InvaderBody::InvaderBody()
  : cnv(GEO_INV_GRID_DIM * GEO_PIXEL_SIZE * 2, GEO_INV_GRID_DIM * GEO_PIXEL_SIZE * 2) {
  generatePattern();
  generateBitmap();
  bufferCopy = new uint8_t[GEO_INV_GRID_DIM * GEO_PIXEL_SIZE * 2 * GEO_INV_GRID_DIM * GEO_PIXEL_SIZE * 2 / 8]; // 1 bit buffer
  updateBufferCopy();
}

void InvaderBody::generatePattern() {
  float maxVal = 0.0;
  uint8_t actualInvSize = int(random(5, GEO_INV_GRID_DIM + 1));
  uint8_t delta = GEO_INV_GRID_DIM - actualInvSize;
  float softGrid[GEO_INV_GRID_DIM][GEO_INV_GRID_DIM];
  for (uint8_t i = 0; i < delta; i++) {
    for (uint8_t j = 0; j < GEO_INV_GRID_DIM; j++) {
      softGrid[i][j] = 0;
    }
  }
  for (uint8_t i = delta; i < GEO_INV_GRID_DIM; i++) {
    for (uint8_t j = 0; j < GEO_INV_GRID_DIM; j++) {
      float val = random(200) / 100.0;  // Random value between 0 and 2
      val += sin(PI * 90 * (i - delta) / GEO_INV_GRID_DIM / 180);
      val += sin(PI * 180 * j / GEO_INV_GRID_DIM / 180);
      maxVal = max(maxVal, val);
      softGrid[i][j] = val;
    }
  }

  // Normalizing and calculating the threshold
  float sum = 0;
  uint8_t count = 0;
  for (uint8_t i = 0; i < GEO_INV_GRID_DIM; i++) {
    for (uint8_t j = 0; j < GEO_INV_GRID_DIM; j++) {
      softGrid[i][j] /= maxVal;
      sum += softGrid[i][j];
      if (softGrid[i][j] != 0) {
        count++;
      }
    }
  }
  float threshold = sum / count;
  // Update grid with boolean values
  for (uint8_t i = 0; i < GEO_INV_GRID_DIM; i++) {
    for (uint8_t j = 0; j < GEO_INV_GRID_DIM; j++) {
      sourceGrid[i][j] = false;
      sourceGrid[i][j] = softGrid[i][j] > threshold;
    }
  }
}

void InvaderBody::generateBitmap() {
  int topLeftX = GEO_INV_GRID_DIM * GEO_PIXEL_SIZE;
  int topLeftY = GEO_INV_GRID_DIM * GEO_PIXEL_SIZE;
  for (int isMirrored = 0; isMirrored <= 1; isMirrored++) {
    for (int i = 0; i < GEO_INV_GRID_DIM; i++) {
      for (int j = 0; j < GEO_INV_GRID_DIM; j++) {
        if (sourceGrid[isMirrored ? GEO_INV_GRID_DIM - i - 1 : i][j]) {
          int xPos = topLeftX + (isMirrored ? i : i - GEO_INV_GRID_DIM) * GEO_PIXEL_SIZE;
          int yPos = topLeftY + j * GEO_PIXEL_SIZE - GEO_INV_GRID_DIM / 2 * GEO_PIXEL_SIZE;
          cnv.fillRect(xPos, yPos, GEO_PIXEL_SIZE, GEO_PIXEL_SIZE, COL_GREEN);
        }
      }
    }
  }
}
