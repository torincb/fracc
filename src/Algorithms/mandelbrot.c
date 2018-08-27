#include <stdio.h>
#include <stdlib.h>


#define MAX_ITER 100


/* don't mess with this lol */
#define C_MODE
#define MAX_ITER 100
#include "mandelbrot_kernel.cl"


int main()
{
    int w, h;
    int x, y;
    double re_min, re_max, im_min, im_max;
    double re, im;
    double *buf;
    FILE *fp;

    w = 2000;
    re_min = -2;
    re_max =  1;
    im_min = -1;
    im_max =  1;

    /* required: w / h = (re_max - re_min) / (im_max - im_min)
     * therefore: h = w(im_max - im_min) / (re_max - re_min)
     */
    h = (int)((double)w*(im_max - im_min) / (re_max - re_min));

    buf = malloc(sizeof *buf * w * h);

    printf("Calculating...\n");
    for (x = 0; x < w; ++x) {
        re = re_min + (double)x*(re_max - re_min) / (double)w;
        for (y = 0; y < h; ++y) {
            im = im_max - (double)y*(im_max - im_min) / (double)h;
            mandelbrot(&re, &im, &buf[x + y*w]);
        }
    }

    printf("Writing...\n");
    fp = fopen("mandelbrot.txt", "w");
    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            fprintf(fp, "%f", buf[x + y*w]);
            if (w - x > 1) {
                fprintf(fp, ",");
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return 0;
}
