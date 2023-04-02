#pragma once
#include "Filters.h"

class GsFilter : public Filter {
public:
    void ApplyFilter(BMPImage& image) override;

private:
    const float r_coefficient_ = 0.299;
    const float g_coefficient_ = 0.587;
    const float b_coefficient_ = 0.114;
};