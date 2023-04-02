#include "Parser.h"
#include "Reader.h"
#include "Writer.h"
#include "Controller.h"
#include "Exceptions.h"
#include <iostream>

int main(int argc, char** argv) {
    Parser input;
    try {
        input = Parser(argc, argv);
    } catch (const ManualExceptions& e) {
        std::cout << e.what();
        return 1;
    } catch (const NumberOfParametersExceptions& e) {
        std::cout << e.what();
        return 1;
    }
    BMPImage image;
    try {
        image = Reader::LoadFile(input.input_path);
    } catch (const ReadExceptions& e) {
        std::cout << e.what();
        return 1;
    } catch (const OpenExceptions& e) {
        std::cout << e.what();
        return 1;
    } catch (const NotBmpExceptions& e) {
        std::cout << e.what();
        return 1;
    } catch (const BitsCountExceptions& e) {
        std::cout << e.what();
        return 1;
    }
    Controller x(image, input.args);
    try {
        x.ApplyFilters();
    } catch (const FilterParametersExceptions& e) {
        std::cout << e.what();
        return 1;
    } catch (const FilterNamesExceptions& e) {
        std::cout << e.what();
        return 1;
    }

    auto image2 = x.GetImage();
    try {
        Writer::SaveFile(input.output_path, image2);
    } catch (const OpenExceptions& e) {
        std::cout << e.what();
        return 1;
    } catch (const WriteExceptions& e) {
        std::cout << e.what();
        return 1;
    }
    return 0;
}
