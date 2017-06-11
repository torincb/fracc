#include "MandelbrotTests.h"

// #include <cstdio>
// #include <cstring>
// #include <SDL2/SDL.h>

// #define WIDTH 1280
// #define HEIGHT 720

/*
 * Work in progress...
 *
namespace fracc
{
    class CLIOptions
    {
        public:
            CLIOptions(int argc, char **argv);

            int width();
            int height();

        private:
            int m_width, m_height;
    };

    CLIOptions::CLIOptions(int argc, char **argv)
        : m_width(1280), m_height(720)
    {
        bool got_width = false;
        bool got_height = false;
        char **arg = argv;

        for (arg = argv; arg < argv + argc; ++arg)
        {
            if (!strcmp(*arg, "-w") || !strcmp(*arg, "--width"))
            {
                
        }
    }
}
*/

int main(int argc, char **argv)
{
    //QApplication fracc(argc, argv);
    //	
    //FraccWindow fracc_window;
    //fracc_window.show();
    //
    //return fracc.exec();

    // temp: Mandelbrot set performance testing
    MandelbrotTests tests;
    tests.serialCPUTimingTest();
    tests.getMandelbrotInstance().writeToBMP("mandelbrot_test.bmp");
 
    return 0;
}
