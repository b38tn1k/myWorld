#include "Landscape.h"

Landscape::Landscape()
  : ProceduralDrawingItem(int(GEO_DISPLAY_WIDTH / GEO_PIXEL_SIZE), int(GEO_DISPLAY_HEIGHT / GEO_PIXEL_SIZE), 1) {
  generatePattern();
  generateBitmap();
  updateBufferCopy();
}

void Landscape::generatePattern() {
  Perlin perlinNoise(GEO_DISPLAY_WIDTH / GEO_PIXEL_SIZE, GEO_DISPLAY_HEIGHT / GEO_PIXEL_SIZE);
  float zoom = 2.;
  float x = zoom / gridXSize;
  float y = zoom / gridYSize;
  float minPerl = 2;
  float maxPerl = -2;

  for (int i = 0; i < gridXSize; i++) {
    for (int j = 0; j < gridYSize; j++) {
      softGrid[i][j] = perlinNoise.noise(x * i, y * j);
      Serial.println(softGrid[i][j]);
      if (softGrid[i][j] < minPerl) {
        minPerl = softGrid[i][j];
      }
      if (softGrid[i][j] > maxPerl) {
        maxPerl = softGrid[i][j];
      }
    }
  }

  float threshold = (minPerl + maxPerl) * 0.9;


  for (int i = 0; i < gridXSize; i++) {
    for (int j = 0; j < gridYSize; j++) {
      if (softGrid[i][j] > threshold) {
        sourceGrid[i][j] = true;
      } else {
        sourceGrid[i][j] = false;
      }
    }
  }
}

void Landscape::generateBitmap() {
  // Loop through each cell in the grid and draw rectangles where needed
  for (int i = 0; i < gridXSize; i++) {
    for (int j = 0; j < gridYSize; j++) {
      if (sourceGrid[i][j] == 1) {
        int xPos = i * GEO_PIXEL_SIZE;
        int yPos = j * GEO_PIXEL_SIZE;
        cnv.fillRect(xPos, yPos, GEO_PIXEL_SIZE, GEO_PIXEL_SIZE, COL_WHITE);
      }
    }
  }
}