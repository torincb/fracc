#include "Mandelbrot.h"
#include <algorithm>
//#include <fstream>
#include <cstdio>
#include <iostream>
#include <png.h>
#include <SDL.h>


Mandelbrot::Mandelbrot() : Mandelbrot(-2.0 + 1.25i, 1.0 - 1.25i, 1920) {}


Mandelbrot::Mandelbrot(ComplexPoint top_left,
                       ComplexPoint bottom_right,
                       int          width_pixels)
: top_left(top_left),
  bottom_right(bottom_right),
  width_pixels(width_pixels),
  generated(false)
{
    calculateDimensions();
}


Mandelbrot::~Mandelbrot()
{
}


void Mandelbrot::generate(int iterations)
{
    if (width_pixels == 0  || height_pixels == 0) {
        std::cerr << "Dimensions invalid.\n";
        return;
    }

    // initialize pixel array to opaque black
    img = std::vector<uint32_t>(width_pixels * height_pixels);
    std::fill(img.begin(), img.end(), 0xFF000000);

    double width  = bottom_right.real() - top_left.real();
    double height = top_left.imag() - bottom_right.imag();

    double pixel_unit_x = width  / (double)width_pixels;
    double pixel_unit_y = height / (double)height_pixels;

    ComplexPoint c, z;
    c = top_left;

    for (int y = 0; y < height_pixels; ++y) {

        // reset the real component (new row)
        c.real(top_left.real());

        for (int x = 0; x < width_pixels; ++x) {

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

            // move 1 pixel along real axis
            c.real(c.real() + pixel_unit_x);
        }

        // Move down 1 pixel on the imaginary axis (new row)
        c.imag(c.imag() - pixel_unit_y);
    }

    generated = true;
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

    // use: width / height = p_width / p_height

    if (width_pixels != 0) {
        height_pixels = (int)((double)width_pixels * height / width);
    } else if (height_pixels != 0) {
        width_pixels = (int)((double)height_pixels * width / height);
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

    FILE *out_file = fopen("mandelbrot.png", "wb");
    if (!out_file) {
        std::cerr << "Couldn't open PNG file for writing.\n";
        return;
    }

    png_structp png_ptr = png_create_write_struct(
        PNG_LIBPNG_VER_STRING,
        NULL, NULL, NULL);
    if (!png_ptr) {
        std::cerr << "png_create_write_struct failed\n";
        return;
    }

    png_infop png_info_ptr = png_create_info_struct(png_ptr);
    if (!png_info_ptr) {
        std::cerr << "png_create_info_struct failed\n";
        png_destroy_write_struct(&png_ptr, NULL);
        return;
    }

    png_init_io(png_ptr, out_file);
}
