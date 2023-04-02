#pragma once
#include "Filters.h"

class CropFilter : public Filter {
public:
    CropFilter(int64_t width, int64_t height);

    void ApplyFilter(BMPImage& image) override;

private:
    int64_t width_;
    int64_t height_;
};