#include "Mandelbrot.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <SDL.h>


Mandelbrot::Mandelbrot() : Mandelbrot(-2.0 + 1.25i, 1.0 - 1.25i, 1920) {}


Mandelbrot::Mandelbrot(ComplexPoint top_left,
                       ComplexPoint bottom_right,
                       int          width_pixels)
: top_left(top_left),
  bottom_right(bottom_right),
  width_pixels(width_pixels)
{
    calculateDimensions();
}


void Mandelbrot::generate(int iterations)
{
    if (width_pixels == 0  || height_pixels == 0) {
        std::cerr << "Dimensions invalid.\n";
        return;
    }

    std::cout << "Reserving for " << width_pixels << " x " << height_pixels << " pixels.\n";

    // initialize pixel array to opaque black
    img = std::vector<uint32_t>(width_pixels * height_pixels);
    std::fill(img.begin(), img.end(), 0xFF000000);

    double width  = bottom_right.real() - top_left.real();
    double height = top_left.imag() - bottom_right.imag();

    int progress = 0;

    ComplexPoint c, z;

    for (int y = 0; y < height_pixels; ++y) {
        for (int x = 0; x < width_pixels; ++x) {

            c = top_left + ComplexPoint( (double)x * width  / (double)width_pixels,
                                        -(double)y * height / (double)height_pixels);
            z = 0;

            // the famed Mandelbrot algorithm
            for (int i = 0; i < iterations; ++i) {
                z = z*z + c;
                if (std::abs(z) > 2) {

                    // This pixel diverges, so we'll shade it according to how quickly it did so
                    // (grayscale only, for now)

                    uint32_t shade = (uint32_t)((float)0xFF * (1.0 - (float)i / (float)iterations));
                    uint32_t pixel = 0xFF000000 | (shade << 16) | (shade << 8) | shade;

                    img[x + y * width_pixels] = pixel;
                    break;
                }
            }

            // a kinda progress bar
            ++progress;
            std::cout << (float)progress / (float)(width_pixels * height_pixels) * 100.0 << "%    \r";
        }
    }

    // temp: use SDL to save to a BMP for debugging
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(
        img.data(),       // pixels
        width_pixels,     // width
        height_pixels,    // height
        32,               // depth (bits)
        width_pixels * 4, // pitch (pixel row in bytes)
        0x00FF0000,       // R mask
        0x0000FF00,       // G mask
        0x000000FF,       // B mask
        0xFF000000);      // A mask

    if (surface == NULL) {
        std::cerr << "Transferring image to SDL surface failed: " << SDL_GetError() << "\n";
        return;
    }

    if (SDL_SaveBMP(surface, "mandelbrot.bmp") != 0) {
        std::cerr << "Saving to BMP failed: " << SDL_GetError() << "\n";
    }
}


ComplexPoint Mandelbrot::getTopLeft()
{
    return top_left;
}


ComplexPoint Mandelbrot::getBottomRight()
{
    return bottom_right;
}


ComplexPoint Mandelbrot::getPixelWidth()
{
    return width_pixels;
}


ComplexPoint Mandelbrot::getPixelHeight()
{
    return height_pixels;
    //return width_pixels * (bottom_right.imag() - top_left.imag())
    //    / (bottom_right.real() - top_left.real());
}


void Mandelbrot::setTopLeft(ComplexPoint p)
{
    top_left = p;
    calculateDimensions();
}


void Mandelbrot::setBottomRight(ComplexPoint p)
{
    bottom_right = p;
    calculateDimensions();
}


void Mandelbrot::setPixelWidth(int n)
{
    width_pixels = n;
    calculateDimensions();
}


void Mandelbrot::setPixelHeight(int n)
{
    height_pixels = n;
    width_pixels = 0;
    calculateDimensions();
}


void Mandelbrot::calculateDimensions()
{
    // Given complex coordinates of top-left and bottom-right of the image and
    // the pixel width of the image, calculate the appropriate pixel height. If
    // the pixel width is 0, use the pixel height to calculate the pixel width
    // instead.

    double width = bottom_right.real() - top_left.real();
    double height = top_left.imag() - bottom_right.imag();

    std::cout << "width: " << width << ", height: " << height << "\n";

    // use: width / height = p_width / p_height

    if (width_pixels != 0) {
        height_pixels = (int)((double)width_pixels * height / width);
    } else if (height_pixels != 0) {
        width_pixels = (int)((double)height_pixels * width / height);
    } else {
        std::cerr << "No pixel dimensions given!\n";
    }
}