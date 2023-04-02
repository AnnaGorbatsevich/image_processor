# image_processor
Supported files: BMP 24-bits

Instruction:

Order of arguments: {programme name} {input path} {output path} [-{name of first filter}, {parameters of first filter}] [-{name of second filter}, {parameters of second filter}] ...

Filters:
1. Сrop (-crop width height)
2. Edge Detection (-edge threshold), example -edge 0.1
3. Sharpening (-sharp)
4. Negative (-neg)
5. Grayscale (-gs)
6. Gaussian Blur (-blur sigma), example -blur 7.5
7. Spheres of Salvador Dali (-spheres amount threshold), example 5 0.02

Example: lenna.bmp output.bmp -crop 500 500 -neg -blur -gs -crop 100 500
