#include "BMPImage.h"

#include <iostream>
#include <cstring>

void BMPImage::Print() {
    uint8_t height = data_.size();
    uint32_t width = data_[0].size();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            std::cout << static_cast<int>(data_[i][j].r) << " " << static_cast<int>(data_[i][j].g) << " "
                      << static_cast<int>(data_[i][j].b) << " | ";
        }
        std::cout << "\n";
    }
}

/*std::vector<std::vector<BMPImage::Pixel>> &BMPImage::GetPixels() {
    return data_;
}*/

uint32_t &BMPImage::GetHor() {
    return ppm_hor_;
}

uint32_t &BMPImage::GetVert() {
    return ppm_vert_;
}

void BMPImage::Crop(size_t width, size_t height) {
    std::reverse(data_.begin(), data_.end());
    if (height < data_.size()) {
        data_.resize(height);
    }
    for (size_t i = 0; i < data_.size(); ++i) {
        if (width > data_[0].size()) {
            break;
        }
        data_[i].resize(width);
    }
    std::reverse(data_.begin(), data_.end());
}

void BMPImage::Resize(size_t width, size_t height) {
    data_.assign(height, std::vector<Pixel>(width));
}

BMPImage::Pixel &BMPImage::At(size_t x, size_t y) {
    return data_[x][y];
}

size_t BMPImage::Height() {
    return data_.size();
}
size_t BMPImage::Width() {
    return data_[0].size();
}