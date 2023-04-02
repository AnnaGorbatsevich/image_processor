#include <catch.hpp>
#include "CropFilter.h"
#include "Exceptions.h"

TEST_CASE("Crop1") {
    BMPImage image;
    const size_t height = 10;
    const size_t width = 20;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = i * width + j;
        }
    }
    bool is_correct = true;
    const size_t new_height = 5;
    const size_t new_width = 10;
    CropFilter cf(new_width, new_height);
    cf.ApplyFilter(image);
    if (image.Height() != std::min(new_height, height) || image.Width() != std::min(new_width, width)) {
        is_correct = false;
    } else {
        for (size_t i = 0; i < std::min(new_height, height); ++i) {
            for (size_t j = 0; j < std::min(new_width, width); ++j) {
                if (image.At(i, j).r != 0 || image.At(i, j).g != 0 ||
                    image.At(i, j).b != (i + height - std::min(new_height, height)) * width + j) {
                    is_correct = false;
                }
            }
        }
    }
    REQUIRE(is_correct);
}

TEST_CASE("Crop2") {
    BMPImage image;
    const size_t height = 10;
    const size_t width = 20;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = i * width + j;
        }
    }
    const size_t new_height = 5;
    const size_t new_width = 30;
    CropFilter cf(new_width, new_height);
    cf.ApplyFilter(image);
    if (image.Height() != std::min(new_height, height) || image.Width() != std::min(new_width, width)) {
        REQUIRE(false);
    } else {
        REQUIRE(true);
    }
}

TEST_CASE("Crop3") {
    BMPImage image;
    const size_t height = 12;
    const size_t width = 20;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = i * width + j;
        }
    }
    bool is_correct = true;
    const size_t new_height = 15;
    const size_t new_width = 30;
    CropFilter cf(new_width, new_height);
    cf.ApplyFilter(image);
    for (size_t i = 0; i < std::min(new_height, height); ++i) {
        for (size_t j = 0; j < std::min(new_width, width); ++j) {
            if (image.At(i, j).r != 0 || image.At(i, j).g != 0 ||
                image.At(i, j).b != (i + height - std::min(new_height, height)) * width + j) {
                is_correct = false;
            }
        }
    }
    REQUIRE(is_correct);
}