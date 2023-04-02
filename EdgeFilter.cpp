#include "EdgeFilter.h"
#include "GsFilter.h"

EdgeFilter::EdgeFilter(double threshold) {
    matrix_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    threshold_ = threshold;
}

void EdgeFilter::ApplyFilter(BMPImage &image) {
    uint32_t height = image.Height();
    uint32_t width = image.Width();
    GsFilter gs_filter = GsFilter();
    gs_filter.ApplyFilter(image);
    MatrixFilter::ApplyFilter(image);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (static_cast<float>(image.At(i, j).r) > threshold_ * static_cast<float>(max_color)) {
                image.At(i, j).r = image.At(i, j).g = image.At(i, j).b = max_color;
            } else {
                image.At(i, j).r = image.At(i, j).g = image.At(i, j).b = 0;
            }
        }
    }
}
