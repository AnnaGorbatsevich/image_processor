#include <catch.hpp>
#include "Writer.h"
#include "SpheresFilter.h"
#include "BMP.h"

TEST_CASE("AddCircle") {
    BMPImage image;
    const size_t height = 1000;
    const size_t width = 2000;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = bmp::MAX_COLOR;
            image.At(i, j).b = bmp::MAX_COLOR;
        }
    }
    const int32_t radius = 50;
    BMPImage::Pixel pi;
    pi.r = bmp::MAX_COLOR;
    pi.b = bmp::MAX_COLOR;
    pi.g = 0;
    const size_t size = 1000;
    std::vector<std::vector<BMPImage::Pixel>> colors(2 * radius, std::vector<BMPImage::Pixel>(2 * radius, pi));
    SpheresFilter::AddCircle(size, size, radius, colors, 1.0, image);

    try {
        Writer::SaveFile(
            "output.bmp",
            image);
        REQUIRE(true);
    } catch (const std::exception& e) {
        REQUIRE(false);
    }
}

TEST_CASE("Circles") {
    BMPImage image;
    const size_t height = 2000;
    const size_t width = 2000;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = bmp::MAX_COLOR;
        }
    }
    const uint32_t amount = 5;
    const double threshold = 0.1;
    SpheresFilter filter(amount, threshold);
    filter.ApplyFilter(image);

    try {
        Writer::SaveFile(
            "output.bmp",
            image);
        REQUIRE(true);
    } catch (const std::exception& e) {
        REQUIRE(false);
    }
}