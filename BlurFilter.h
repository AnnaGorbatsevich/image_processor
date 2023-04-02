#pragma once
#include "Filters.h"

class BlurFilter : public Filter {
public:
    explicit BlurFilter(double sigma);
    void ApplyFilter(BMPImage& image) override;

private:
    double sigma_;
    std::vector<double> multiplier_;
    int32_t step_;
};
