//#include <QApplication>
//#include "FraccWindow.h"

#include "Mandelbrot.h"

int main(int argc, char **argv)
{
    //QApplication fracc(argc, argv);
    //	
    //FraccWindow fracc_window;
    //fracc_window.show();
    //
    //return fracc.exec();

    // temp: generate the Mandelbrot set
    Mandelbrot mandelbrot;
    mandelbrot.generate(100); //100 iteration test

    return 0;
}
