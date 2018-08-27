#define CUTOFF_MAGN_SQ 4.0

#ifndef MAX_ITER
  #define MAX_ITER 100
#endif

#ifdef C_MODE
  #include <math.h>
  #define __kernel
  #define __global
#endif


double cmp_abs_sq(double re, double im) {
    /* |x + iy|^2
     * = (x + iy)(x - iy)
     * = x^2 + y^2
     */
    return re*re + im*im;
}


__kernel void mandelbrot(__global const double *g_re, __global const double *g_im, __global double *g_res)
{
    double z_re = 0.0;
    double z_im = 0.0;
    int i;

    double log_zn, nu;

    __global const double *re, *im;
    __global double *res;

#ifdef C_MODE
    re = g_re;
    im = g_im;
    res = g_res;
#else
    int gid = get_global_id(0);
    re = &(g_re[gid]);
    im = &(g_im[gid]);
    res = &(g_res[gid]);
#endif

    for (i = 0; i < MAX_ITER && cmp_abs_sq(z_re, z_im) < CUTOFF_MAGN_SQ; ++i) {
        /* z_{n+1} = z_n^2 + c
         * (x + iy)^2 = x^2 - y^2 + 2ixy
         */
        double z_re_tmp = z_re*z_re - z_im*z_im + *re;
        z_im = 2*z_re*z_im + *im;
        z_re = z_re_tmp;
    }

    if (i < MAX_ITER) {
        log_zn = log(cmp_abs_sq(z_re, z_im)) / 2.0;
        nu = log(log_zn / log(2.0)) / log(2.0);
    } else {
        nu = 1.0;
    }

    *res = (double)i + 1.0 - nu;
}
