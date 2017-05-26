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

    ~Mandelbrot();

    void                  generate  (int iterations);
    void                  writeToBMP(const char *filename) const;

    ComplexPoint          getTopLeft();
    ComplexPoint          getBottomRight();
    ComplexPoint          getPixelWidth();
    ComplexPoint          getPixelHeight();

    void                  setTopLeft    (ComplexPoint p);
    void                  setBottomRight(ComplexPoint p);
    void                  setPixelWidth (int n);
    void                  setPixelHeight(int n);

private:
    ComplexPoint          top_left;
    ComplexPoint          bottom_right;

    int                   width_pixels;
    int                   height_pixels;

    std::vector<uint32_t> img;

    bool                  generated;

    void                  calculateDimensions();
    void                  writeToPNG();
};


#endif