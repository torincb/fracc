#include "LinearColourMap.h"


LinearColourMap::LinearColourMap(uint32_t start_colour, uint32_t end_colour)
{
    segment_joints.push_back(ColourSegmentJoint(start_colour, 0.0));
    segment_joints.push_back(ColourSegmentJoint(end_colour, 1.0));
}


LinearColourMap::~LinearColourMap() {}


uint32_t LinearColourMap::getColour(float value)
{
    // unfinished
    return false;
}


void LinearColourMap::setStartColour(uint32_t colour)
{
    segment_joints[0].colour = colour;
}


void LinearColourMap::setEndColour(uint32_t colour)
{
    segment_joints.back().colour = colour;
}


bool LinearColourMap::addJoint(ColourSegmentJoint joint)
{
    // unfinished
    return false;
}