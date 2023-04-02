#pragma once
#include "MatrixFilter.h"

class EdgeFilter : public MatrixFilter {
public:
    explicit EdgeFilter(double threshold);
    void ApplyFilter(BMPImage& image) override;

private:
    double threshold_;
};
