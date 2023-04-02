#include "NegFilter.h"

void NegFilter::ApplyFilter(BMPImage& image) {
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            image.At(i, j).r = max_color_ - image.At(i, j).r;
            image.At(i, j).g = max_color_ - image.At(i, j).g;
            image.At(i, j).b = max_color_ - image.At(i, j).b;
        }
    }
}