#pragma once
#include "Filters.h"

class SpheresFilter : public Filter {
public:
    SpheresFilter(uint32_t amount, double threshold);
    void ApplyFilter(BMPImage& image) override;
    static void AddCircle(int32_t x, int32_t y, int32_t radius, const std::vector<std::vector<BMPImage::Pixel>>& colors,
                   double blackout, BMPImage& image);

private:
    uint32_t balls_amount_;
    double threshold_;
    const double blackout_coef_ = 11.0 / 9;
    const size_t the_least_size_ = 100;
};
