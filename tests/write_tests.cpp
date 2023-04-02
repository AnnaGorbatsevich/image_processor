#include <catch.hpp>
#include "Writer.h"
#include "Exceptions.h"

TEST_CASE("CorrectWrite") {
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
    try {
        Writer::SaveFile("result.bmp", image);
        REQUIRE(true);
    } catch (const std::exception& e) {
        REQUIRE(false);
    }
}

TEST_CASE("NotBmpWrite") {
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
    REQUIRE_THROWS_AS(Writer::SaveFile("result.jpeg", image), NotBmpExceptions);
}