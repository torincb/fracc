# Fracc - free fractal fun
This is in early development! It will eventually be a suite for rendering 2D and 3D fractals of many types, supporting various hardware and rendering software.

## Goals
Some rough goals for the project are:
* **Usability**: Casual users should be able to use the program to create basic renders without hassle, e.g. run-of-the-mill Mandelbrot renders.
* **Power**: The suite should be suitable for heavy-duty usage, such as by artists or researchers. Expansive configuration options should be readily available if they are not shown by default.
* **Dimensionality**: The suite should support 2D and 3D renders. 4D renders may also be possible in the form of 3D slices.
* **Cross-platform support**: The suite will run on at least the following platforms, initially: Linux and Windows. Support for BSDs and macOS will be added in the future. Porting however should not be difficult, with cross-platform compatibility in mind from the start.
* **Hardware support**: CPU and GPU renders will be supported. Technology such as CUDA and OpenCL should be utilised. The suite will provide easy configuration of hardware used.

## Why?
I've been interested in fractals for as long as I can remember! I have used a variety of programs to produce renders, but none are as expansive as I'd like. Mandelbulb 3D is a great tool and a labour of love, but as far as I know, it lacks support for 4D fractals (quaternion slices) and is designed specifically for 3D rather than 2D renders. It is also not under a free software license. It would be great to have a totally free suite with some community-driven development!

## The plan
I will be adding to this repository slowly. There is essentially nothing here yet. If you are interested as a potential user or developer, feel free to star the repository or get in touch.

## Technologies
I plan to develop in Python, using Qt for the GUI. The plan is for algorithms to be written as a C snippet, and executable as either C or OpenCL code.
