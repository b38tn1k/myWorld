// Invader.h
#ifndef InvaderBody_h
#define InvaderBody_h

#include "Arduino.h"
#include "Arduino_GigaDisplay_GFX.h"
#include "constants.h"

class InvaderBody {
private:


public:
  InvaderBody();
  ~InvaderBody() {
    delete[] bufferCopy;
  }
  GFXcanvas1 cnv;
  uint8_t* bufferCopy;
  bool sourceGrid[GEO_INV_GRID_DIM][GEO_INV_GRID_DIM];
  void generatePattern();
  void generateBitmap();
  void updateBufferCopy() {
    memcpy(bufferCopy, cnv.getBuffer(), GEO_INV_GRID_DIM * GEO_PIXEL_SIZE * 2 * GEO_INV_GRID_DIM * GEO_PIXEL_SIZE * 2 / 8);
  }
  uint8_t* getBufferCopy() const {
    return bufferCopy;
  }
};

#endif
