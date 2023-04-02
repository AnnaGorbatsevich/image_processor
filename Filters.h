#pragma once
#include <vector>
#include <string>
#include "BMPImage.h"
#include <iostream>

class Filter {
public:
    Filter();
    virtual void ApplyFilter(BMPImage& image);
    virtual ~Filter();
};
