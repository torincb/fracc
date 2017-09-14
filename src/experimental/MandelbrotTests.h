#ifndef MANDELBROTTESTS_H
#define MANDELBROTTESTS_H

#include "Mandelbrot.h"


class MandelbrotTests {
public:
    MandelbrotTests();
    ~MandelbrotTests();

    void              serialCPUTimingTest();

    const Mandelbrot& getMandelbrotInstance();

private:
    Mandelbrot        brot_instance;
};


#endif