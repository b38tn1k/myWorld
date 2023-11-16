#ifndef Landscape_h
#define Landscape_h

#include "ProceduralDrawingItem.h"

class Landscape : public ProceduralDrawingItem {
public:
    Landscape();
    void generatePattern() override;
    void generateBitmap() override;
};

#endif
