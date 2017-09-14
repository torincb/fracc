#include "MandelbrotTests.h"
#include "Mandelbrot.h"
#include <chrono>
#include <cstdlib>
#include <iostream>


MandelbrotTests::MandelbrotTests()
{
    ComplexPoint centre = -.743643135 + .131825963i;
    double width = 0.000014628;
    double aspect_ratio = 800./600.;
    double height = width / aspect_ratio;

    ComplexPoint top_left, bottom_right;

    top_left.real(centre.real() - width / 2.0);
    bottom_right.real(centre.real() + width / 2.0);

    top_left.imag(centre.imag() + height / 2.0);
    bottom_right.imag(centre.imag() - height / 2.0);

    brot_instance = Mandelbrot(top_left, bottom_right, 1280);
}


MandelbrotTests::~MandelbrotTests()
{

}


void MandelbrotTests::serialCPUTimingTest()
{
    // brot_instance has already been initialized with default values

    auto start = std::chrono::high_resolution_clock::now();

    brot_instance.generate(1000);

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Test took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0
              << " seconds.\n";
}


const Mandelbrot& MandelbrotTests::getMandelbrotInstance()
{
    return brot_instance;
}