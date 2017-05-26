#ifndef LINEARCOLOURMAP_H
#define LINEARCOLOURMAP_H

#include "ColourMapBase.h"
#include <utility>
#include <vector>


struct ColourSegmentJoint {
    uint32_t colour;
    float position;

    ColourSegmentJoint(uint32_t colour, float position)
        : colour(colour), position(position) {}
};


class LinearColourMap: public ColourMapBase {
public:
    LinearColourMap(uint32_t start_colour = 0xFFFFFFFF,
                    uint32_t end_colour   = 0x00000000);
    ~LinearColourMap();

    uint32_t getColour(float value);

    void     setStartColour(uint32_t colour);
    void     setEndColour(uint32_t colour);
    bool     addJoint(ColourSegmentJoint joint);

private:
    std::vector<ColourSegmentJoint> segment_joints;
};


#endif