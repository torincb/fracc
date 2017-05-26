//#include <QApplication>
//#include "FraccWindow.h"

#include "MandelbrotTests.h"

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