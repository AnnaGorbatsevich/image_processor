#pragma once

#include <string>
#include <vector>

class BMPImage {
public:
    struct Pixel {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        Pixel() {
            r = 0;
            g = 0;
            b = 0;
        }
    };
    void Print();
    BMPImage() = default;
    // std::vector<std::vector<Pixel>>& GetPixels();
    uint32_t& GetHor();
    uint32_t& GetVert();
    void Resize(size_t width, size_t height);
    void Crop(size_t width, size_t height);
    Pixel& At(size_t x, size_t y);
    size_t Height();
    size_t Width();

private:
    std::vector<std::vector<Pixel>> data_;
    uint32_t ppm_hor_;
    uint32_t ppm_vert_;
};
