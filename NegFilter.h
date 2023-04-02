#pragma once
#include "Filters.h"

class NegFilter : public Filter {
public:
    void ApplyFilter(BMPImage& image) override;

private:
    const uint8_t max_color_ = 255;
};