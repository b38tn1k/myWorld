#ifndef InvaderBody_h
#define InvaderBody_h

#include "ProceduralDrawingItem.h"

class InvaderBody : public ProceduralDrawingItem {
public:
    InvaderBody();
    void generatePattern() override;
    void generateBitmap() override;
};

#endif
