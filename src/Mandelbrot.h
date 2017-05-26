#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <complex>
#include <cstdint>
#include <vector>

typedef std::complex<double> ComplexPoint;


class Mandelbrot {
public:
    Mandelbrot();
    Mandelbrot(ComplexPoint top_left,
               ComplexPoint bottom_right,
               int          width_pixels);

    void         generate(int iterations);

    ComplexPoint getTopLeft();
    ComplexPoint getBottomRight();
    ComplexPoint getPixelWidth();
    ComplexPoint getPixelHeight();

    void         setTopLeft    (ComplexPoint p);
    void         setBottomRight(ComplexPoint p);
    void         setPixelWidth (int n);
    void         setPixelHeight(int n);

private:
    ComplexPoint top_left;
    ComplexPoint bottom_right;

    int          width_pixels;
    int          height_pixels;

    std::vector<uint32_t> img;

    void         calculateDimensions();
};


#endif