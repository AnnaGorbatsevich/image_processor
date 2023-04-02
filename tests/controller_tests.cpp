#include <catch.hpp>
#include "Controller.h"
#include "Exceptions.h"
#include <BMP.h>

TEST_CASE("CorrectController") {
    BMPImage image;
    const size_t height = 10;
    const size_t width = 10;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = bmp::MAX_COLOR;
        }
    }
    std::vector<std::string> filters = {"-crop", "10", "5", "-neg", "-crop", "1", "20"};
    try {
        Controller c(image, filters);
        REQUIRE(c.ApplyFilters());
    } catch (const std::exception& e) {
        REQUIRE(false);
    }
}

TEST_CASE("IncorrectNameController") {
    BMPImage image;
    const size_t height = 1;
    const size_t width = 1;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = bmp::MAX_COLOR;
        }
    }
    std::vector<std::string> filters = {"-cropp", "10", "5", "-neg", "-crop", "1", "20"};
    Controller c(image, filters);
    REQUIRE_THROWS_AS(c.ApplyFilters(), FilterNamesExceptions);
}

TEST_CASE("IncorrectCropController") {
    BMPImage image;
    const size_t height = 2;
    const size_t width = 4;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = bmp::MAX_COLOR;
        }
    }
    std::vector<std::string> filters = {"-crop", "10"};
    Controller c(image, filters);
    REQUIRE_THROWS_AS(c.ApplyFilters(), FilterParametersExceptions);
}

TEST_CASE("IncorrectCropController2") {
    BMPImage image;
    const size_t height = 7;
    const size_t width = 10;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = bmp::MAX_COLOR;
        }
    }
    std::vector<std::string> filters = {"-crop", "10", "0"};
    Controller c(image, filters);
    REQUIRE_THROWS_AS(c.ApplyFilters(), FilterParametersExceptions);
}

TEST_CASE("IncorrectEdgeController") {
    BMPImage image;
    const size_t height = 6;
    const size_t width = 7;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = bmp::MAX_COLOR;
        }
    }
    std::vector<std::string> filters = {"-edge", "-crop", "10", "20"};
    Controller c(image, filters);
    REQUIRE_THROWS_AS(c.ApplyFilters(), FilterParametersExceptions);
}

TEST_CASE("IncorrectEdgeController2") {
    BMPImage image;
    const size_t height = 5;
    const size_t width = 5;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = bmp::MAX_COLOR;
        }
    }
    std::vector<std::string> filters = {"-edge"};
    Controller c(image, filters);
    REQUIRE_THROWS_AS(c.ApplyFilters(), FilterParametersExceptions);
}

TEST_CASE("IncorrectBlurController") {
    BMPImage image;
    const size_t height = 6;
    const size_t width = 1;
    image.Resize(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j).r = image.At(i, j).g = 0;
            image.At(i, j).b = bmp::MAX_COLOR;
        }
    }
    std::vector<std::string> filters = {"-blur", "-crop"};
    Controller c(image, filters);
    REQUIRE_THROWS_AS(c.ApplyFilters(), FilterParametersExceptions);
}
