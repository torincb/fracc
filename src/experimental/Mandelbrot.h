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
               uint32_t     width_pixels);

    ~Mandelbrot();

    void                  generate  (uint32_t iterations);
    void                  writeToBMP(const char *filename) const;

    ComplexPoint          getTopLeft();
    ComplexPoint          getBottomRight();
    ComplexPoint          getPixelWidth();
    ComplexPoint          getPixelHeight();

    void                  setTopLeft    (ComplexPoint p);
    void                  setBottomRight(ComplexPoint p);
    void                  setPixelWidth (uint32_t n);
    void                  setPixelHeight(uint32_t n);

private:
    ComplexPoint          top_left;
    ComplexPoint          bottom_right;

    uint32_t              width_pixels;
    uint32_t              height_pixels;
    uint32_t              max_iterations;

    std::vector<uint32_t> img;
    std::vector<uint32_t> raw_output;
    std::vector<uint32_t> histogram;

    bool                  generated;
    bool                  generated_raw;

    void                  calculateDimensions();
    void                  writeToPNG();
    void                  histogramColouring();
    void                  continuousColouring();
};


#endif