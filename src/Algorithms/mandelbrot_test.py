import numpy as np
import matplotlib
matplotlib.use("Qt5Agg")
import matplotlib.pyplot as plt
import subprocess
import os

USE_C = False


def output_older(out_filename, in_filename):
    try:
        out_stat = os.stat(out_filename)
    except OSError:
        return True
    in_stat = os.stat(in_filename)
    if out_stat.st_mtime > in_stat.st_mtime:
        return False
    return True


def gen_inputs():
    # w = 2000;
    # re_min = -2;
    # re_max =  1;
    # im_min = -1;
    # im_max =  1;
    # h = (int)((double)w*(im_max - im_min) / (re_max - re_min));
    w = 10000
    re_min = -2
    re_max =  1
    im_min = -1
    im_max =  1
    h = int(w*(im_max - im_min)/(re_max - re_min))

    re = np.linspace(re_min, re_max, w, dtype=np.double)
    im = np.linspace(im_min, im_max, h, dtype=np.double)
    grid = np.meshgrid(re, im)

    return h, w, grid[0].flatten(), grid[1].flatten()


if USE_C:
    if output_older("mandelbrot", "mandelbrot.c") or output_older("mandelbrot", "mandelbrot_kernel.cl"):
        print("[py] Compiling...")
        res = subprocess.run("clang -O3 -pedantic -Wall -std=c99 -o mandelbrot mandelbrot.c -lm".split())
        if res.returncode != 0:
            exit()

    if output_older("mandelbrot.txt", "mandelbrot"):
        print("[py] Running...")
        res = subprocess.run("./mandelbrot")
        if res.returncode != 0:
            exit()

    print("[py] Displaying...")
    dat = np.loadtxt("mandelbrot.txt", delimiter=",")
    plt.imshow(dat)
    plt.show()

else:
    print("Setting up OpenCL...")
    import pyopencl as cl
    ctx = cl.create_some_context()
    queue = cl.CommandQueue(ctx)
    mflags = cl.mem_flags
    prog = cl.Program(ctx, open("mandelbrot_kernel.cl").read()).build()

    print("Generating coordinates...")
    rows, cols, re_vals, im_vals = gen_inputs()
    out = np.empty_like(re_vals)

    print(f"est. device memory needed = {out.nbytes*3*2**-30:.3f} GiB")

    print("Allocating device memory...")
    re_buf = cl.Buffer(ctx, mflags.READ_ONLY | mflags.COPY_HOST_PTR, hostbuf=re_vals)
    im_buf = cl.Buffer(ctx, mflags.READ_ONLY | mflags.COPY_HOST_PTR, hostbuf=im_vals)
    out_buf = cl.Buffer(ctx, mflags.WRITE_ONLY, out.nbytes)

    print("Running...")
    prog.mandelbrot(queue, re_vals.shape, None, re_buf, im_buf, out_buf)
    cl.enqueue_copy(queue, out, out_buf)
    out = out.reshape((rows, cols))

    print("Displaying...")
    plt.imshow(out)
    plt.show()

