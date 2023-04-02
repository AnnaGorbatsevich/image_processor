#pragma once

#include "BMPImage.h"
#include <string>

class Reader {
public:
    static BMPImage LoadFile(std::string_view path);
};
