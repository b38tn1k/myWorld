// Invader.h
#ifndef InvaderBody_h
#define InvaderBody_h

#include "Arduino.h"
#include "Arduino_GigaDisplay_GFX.h"
#include "constants.h"

class InvaderBody {
  public:
    InvaderBody();
    GFXcanvas1 cnv;
    bool invaderGrid[GEO_INV_GRID_DIM][GEO_INV_GRID_DIM];
    void generatePattern();
    void generateBitmap();
};

#endif
