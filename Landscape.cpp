#include "Landscape.h"

Landscape::Landscape() : ProceduralDrawingItem(int(GEO_DISPLAY_WIDTH/GEO_PIXEL_SIZE), int(GEO_DISPLAY_HEIGHT/GEO_PIXEL_SIZE), 1) {
    generatePattern();
    generateBitmap();
    updateBufferCopy();
}

void Landscape::generatePattern() {
    // Fill sourceGrid with random 0s and 1s
    for (int i = 0; i < gridXSize; i++) {
        for (int j = 0; j < gridYSize; j++) {
            sourceGrid[i][j] = random(2); // random(2) generates 0 or 1
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