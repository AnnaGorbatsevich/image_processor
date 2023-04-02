#include "Parser.h"
#include "Exceptions.h"

Parser::Parser(int argc, char** argv) {
    if (argc == 1) {
        throw ManualExceptions(
            "Instruction:\n"
            "Supported files: BMP 24-bits\n"
            "Order of arguments: {programme name} {input path} {output path} [-{name of first filter}, {parameters of "
            "first filter}] [-{name of second filter}, {parameters of second filter}] ...\n"
            "Filters:\n"
            "Сrop (-crop width height)\n"
            "Edge Detection (-edge threshold), example -edge 0.1\n"
            "Sharpening (-sharp)\n"
            "Negative (-neg)\n"
            "Grayscale (-gs)\n"
            "Gaussian Blur (-blur sigma), example -blur 7.5\n"
            "Spheres of Salvador Dali (-spheres amount threshold), example 5 0.02\n"
            "Example: lenna.bmp output.bmp -crop 500 500 -neg -blur -gs -crop 100 500\n");

    } else if (argc < 3) {
        throw NumberOfParametersExceptions("not enough parameters");
    }
    input_path = argv[1];
    output_path = argv[2];
    args.resize(argc - 3);
    for (int i = 3; i < argc; ++i) {
        args[i - 3] = argv[i];
    }
}