#ifndef ProceduralDrawingItem_h
#define ProceduralDrawingItem_h

#include "Arduino.h"
#include "Arduino_GigaDisplay_GFX.h"
#include "constants.h"

class ProceduralDrawingItem {
protected:
    uint8_t* bufferCopy;
    GFXcanvas1 cnv;
    int gridXSize;
    int gridYSize;
    bool** sourceGrid;
public:
    ProceduralDrawingItem(int xsize, int ysize, int cnvMult);
    virtual ~ProceduralDrawingItem();
    virtual void generatePattern() = 0; // Pure virtual function
    virtual void generateBitmap() = 0;  // Pure virtual function
    void updateBufferCopy();
    uint8_t* getBufferCopy() const;
    int width;
    int height;
    void logSourceGrid();
};

#endif
