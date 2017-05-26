#include "MandelbrotTests.h"
#include "Mandelbrot.h"
#include <chrono>
#include <iostream>


MandelbrotTests::MandelbrotTests()
{

}


MandelbrotTests::~MandelbrotTests()
{

}


void MandelbrotTests::serialCPUTimingTest()
{
    // brot_instance has already been initialized with default values

    auto start = std::chrono::high_resolution_clock::now();

    brot_instance.generate(100);

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Test took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0
              << " seconds.\n";
}


const Mandelbrot& MandelbrotTests::getMandelbrotInstance()
{
    return brot_instance;
}