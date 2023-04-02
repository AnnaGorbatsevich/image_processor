#pragma once

#include "BMPImage.h"
#include <string>

class Writer {
public:
    static void SaveFile(std::string_view path, BMPImage& image);
};
