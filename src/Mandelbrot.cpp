#include "Mandelbrot.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>

//#include <png.h>
#include <SDL.h>


Mandelbrot::Mandelbrot() : Mandelbrot(-2.0 + 1.25i, 1.0 - 1.25i, 2560) {}


Mandelbrot::Mandelbrot(ComplexPoint top_left,
                       ComplexPoint bottom_right,
                       uint32_t     width_pixels)
: top_left(top_left),
  bottom_right(bottom_right),
  width_pixels(width_pixels),
  max_iterations(100),
  generated(false),
  generated_raw(false)
{
    calculateDimensions();
}


Mandelbrot::~Mandelbrot()
{
}


void Mandelbrot::generate(uint32_t iterations)
{
    if (width_pixels == 0  || height_pixels == 0) {
        std::cerr << "Dimensions invalid.\n";
        return;
    }

    max_iterations = iterations;

    // initialise output arrays
    img        = std::vector<uint32_t>(width_pixels * height_pixels, 0xFF000000);
    raw_output = std::vector<uint32_t>(width_pixels * height_pixels, 0);
    histogram  = std::vector<uint32_t>(max_iterations,               0);

    double width  = bottom_right.real() - top_left.real();
    double height = top_left.imag() - bottom_right.imag();

    double pixel_unit_x = width  / (double)width_pixels;
    double pixel_unit_y = height / (double)height_pixels;

    ComplexPoint c, z;

    for (uint32_t y = 0; y < height_pixels; ++y) {
        c.imag(top_left.imag() - y * pixel_unit_y);

        for (uint32_t x = 0; x < width_pixels; ++x) {
            c.real(top_left.real() + pixel_unit_x * x);

            // check if point is within main cardioid bulb
            double q = pow(c.real() - 0.25, 2) + pow(c.imag(), 2);
            if (q * (q + (c.real() - 0.25)) < 0.25 * pow(c.imag(), 2)) {
                continue;
            }

            // check if point is within period-2 bulb
            if (pow(c.real() + 1, 2) + pow(c.imag(), 2) < 1./16.) {
                continue;
            }

            z = 0;

            // the famed Mandelbrot algorithm (we store the number of
            // iterations taken to escape for each pixel)
            for (uint32_t i = 0; i < max_iterations; ++i) {
                z = z*z + c;
                if (std::abs(z) > 2) {
                    raw_output[x + y * width_pixels] = i;
                    ++histogram[i];
                    break;
                }
            }
        }
    }

    generated_raw = true;

    // TODO: this needs to be an option somewhere
    histogramColouring();
}


void Mandelbrot::writeToBMP(const char *filename) const
{
    if (!generated) {
        std::cerr << "Image not yet generated; cannot save.\n";
        return;
    }

    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(
        (void *) img.data(), // pixels
        width_pixels,        // width
        height_pixels,       // height
        32,                  // depth (bits)
        width_pixels * 4,    // pitch (pixel row in bytes)
        0x00FF0000,          // R mask
        0x0000FF00,          // G mask
        0x000000FF,          // B mask
        0xFF000000);         // A mask

    if (surface == NULL) {
        std::cerr << "Transferring image to SDL surface failed: " << SDL_GetError() << "\n";
        return;
    }

    if (SDL_SaveBMP(surface, filename) != 0) {
        std::cerr << "Saving to BMP failed: " << SDL_GetError() << "\n";
    }

    SDL_FreeSurface(surface);
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


void Mandelbrot::setPixelWidth(uint32_t n)
{
    width_pixels = n;
    calculateDimensions();
}


void Mandelbrot::setPixelHeight(uint32_t n)
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

    // use: width / height = p_width / p_height

    if (width_pixels != 0) {
        height_pixels = (uint32_t)((double)width_pixels * height / width);
    } else if (height_pixels != 0) {
        width_pixels = (uint32_t)((double)height_pixels * width / height);
    } else {
        std::cerr << "No pixel dimensions given!\n";
    }
}


void Mandelbrot::writeToPNG()
{
    std::cerr << "Writing to PNG is unimplemented! Aborting.\n";
    return;
    
    // Unfinished because libPNG is completely unsuitable for this and I need
    // a replacement

//    FILE *out_file = fopen("mandelbrot.png", "wb");
//    if (!out_file) {
//        std::cerr << "Couldn't open PNG file for writing.\n";
//        return;
//    }
//
//    png_structp png_ptr = png_create_write_struct(
//        PNG_LIBPNG_VER_STRING,
//        NULL, NULL, NULL);
//    if (!png_ptr) {
//        std::cerr << "png_create_write_struct failed\n";
//        return;
//    }
//
//    png_infop png_info_ptr = png_create_info_struct(png_ptr);
//    if (!png_info_ptr) {
//        std::cerr << "png_create_info_struct failed\n";
//        png_destroy_write_struct(&png_ptr, NULL);
//        return;
//    }
//
//    png_init_io(png_ptr, out_file);
}


void Mandelbrot::histogramColouring()
{
    if (!generated_raw) {
        std::cerr << "Raw data not yet generated! Aborting render.\n";
        return;
    }

    float total = std::accumulate(histogram.begin(), histogram.end(), 0);

    // generate the normalized colour palette
    std::vector<uint32_t> palette(max_iterations);
    float hue = 0.0;
    for (int i = 0; i < max_iterations; ++i) {
        hue += (float)histogram[i] / total;
        palette[i] = 0xFF000000 | (uint8_t)((float)0xFF * hue);
    }

    std::cout << "Colouring...\n";

    for (int i = 0; i < raw_output.size(); ++i) {
        if (raw_output[i] == 0) {
            img[i] = 0xFF000000;
        } else {
            img[i] = palette[raw_output[i]];
        }
    }

    generated = true;
}


void Mandelbrot::continuousColouring()
{
    std::cerr << "Continuous colouring not yet implemented.\n";

//    if (!generated_raw) {
//        std::cerr << "Raw data not yet generated! Aborting render.\n";
//        return;
//    }
//
//    std::cerr << "Warning: Actually using discrete colouring for now.\n";
//    std::cout << "Colouring...\n";

}