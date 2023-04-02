#include "GsFilter.h"

void GsFilter::ApplyFilter(BMPImage& image) {
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            uint8_t new_color = static_cast<uint8_t>(static_cast<float>(image.At(i, j).r) * r_coefficient_ +
                                                     static_cast<float>(image.At(i, j).g) * g_coefficient_ +
                                                     static_cast<float>(image.At(i, j).b) * b_coefficient_);
            image.At(i, j).r = image.At(i, j).g = image.At(i, j).b = new_color;
        }
    }
}
