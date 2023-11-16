#include "ProceduralDrawingItem.h"

ProceduralDrawingItem::ProceduralDrawingItem(int xsize, int ysize, int cnvMult)
  : cnv(xsize * GEO_PIXEL_SIZE * cnvMult, ysize * GEO_PIXEL_SIZE * cnvMult),
    gridXSize(xsize), gridYSize(ysize) {

  sourceGrid = new bool*[gridXSize];
  for (int i = 0; i < gridXSize; i++) {
    sourceGrid[i] = new bool[gridYSize];
    for (int j = 0; j < gridYSize; j++) {
      sourceGrid[i][j] = false;
    }
  }

  int bufferLength = cnv.width() * cnv.height() / 8;  // Assuming 1-bit per pixel as before
  bufferCopy = new uint8_t[bufferLength];
  width = cnv.width();
  height = cnv.height();
}

ProceduralDrawingItem::~ProceduralDrawingItem() {
  for (int i = 0; i < gridXSize; i++) {
    delete[] sourceGrid[i];
  }
  delete[] sourceGrid;
  delete[] bufferCopy;
}

void ProceduralDrawingItem::updateBufferCopy() {
  memcpy(bufferCopy, cnv.getBuffer(), width * height / 8);  // Copy the entire canvas buffer
}

uint8_t* ProceduralDrawingItem::getBufferCopy() const {
  return bufferCopy;
}

void ProceduralDrawingItem::logSourceGrid() {
  for (int i = 0; i < gridXSize; i++) {
    for (int j = 0; j < gridYSize; j++) {
      Serial.print(sourceGrid[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println();
}