#pragma once
#include "Filters.h"

class MatrixFilter : public Filter {
public:
    MatrixFilter();
    void ApplyFilter(BMPImage& image) override;

protected:
    std::vector<std::vector<int32_t>> matrix_;
    const uint8_t max_color = 255;
};
