#include "CropFilter.h"

CropFilter::CropFilter(int64_t width, int64_t height) {
    width_ = width;
    height_ = height;
}
void CropFilter::ApplyFilter(BMPImage& image) {
    image.Crop(width_, height_);
}
