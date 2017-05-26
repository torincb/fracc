#ifndef COLOURMAPBASE_H
#define COLOURMAPBASE_H

#include <cstdint>


class ColourMapBase {
    /*
    Base class for colour maps, which take a floating point value between 0
    and 1 and assign it to a 32-bit colour.
    */
public:
    virtual uint32_t getColour(float value) = 0;

protected:
    ColourMapBase() {}
};


#endif