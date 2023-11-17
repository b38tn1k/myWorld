#ifndef Landscape_h
#define Landscape_h

#include "ProceduralDrawingItem.h"
#include "Perlin.h"

class Landscape : public ProceduralDrawingItem {
public:
    Landscape();
    void generatePattern() override;
    void generateBitmap() override;
    float softGrid[GEO_DISPLAY_WIDTH / GEO_PIXEL_SIZE][GEO_DISPLAY_HEIGHT / GEO_PIXEL_SIZE];
};

#endif
