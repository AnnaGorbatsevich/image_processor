#include "SpheresFilter.h"
#include "EdgeFilter.h"
#include "Exceptions.h"
#include "BMP.h"
#include <math.h>

void SpheresFilter::ApplyFilter(BMPImage& image) {

    size_t size = std::min(image.Height(), image.Width());
    BMPImage result;

    result.Resize(size, size);
    image.Crop(size, size);
    uint32_t sum_r = 0;
    uint32_t sum_g = 0;
    uint32_t sum_b = 0;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            sum_r += image.At(i, j).r;
            sum_g += image.At(i, j).g;
            sum_b += image.At(i, j).b;
        }
    }
    sum_r /= (size * size) * 2;
    sum_g /= (size * size) * 2;
    sum_b /= (size * size) * 2;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result.At(i, j).r = image.At(i, j).r;
            result.At(i, j).g = image.At(i, j).g;
            result.At(i, j).b = image.At(i, j).b;
        }
    }
    EdgeFilter ed_filter(threshold_);
    ed_filter.ApplyFilter(result);

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            if (result.At(i, j).r == 0) {
                result.At(i, j).r = sum_r;
                result.At(i, j).g = sum_g;
                result.At(i, j).b = sum_b;
            } else {
                result.At(i, j).r = sum_r * 2;
                result.At(i, j).g = sum_g * 2;
                result.At(i, j).b = sum_b * 2;
            }
        }
    }

    size_t current_size = the_least_size_;
    size_t ball_size = current_size / (2 * balls_amount_ - 1);
    if (ball_size == 0) {
        throw FilterParametersExceptions("incorrect parameters for the filter: -spheres");
    }
    double blackout = 1.0 / 4;
    while (current_size <= size + ball_size) {
        ball_size = current_size / (2 * balls_amount_ - 1);
        int32_t offset = (static_cast<int32_t>(size) - static_cast<int32_t>(current_size)) / 2;
        for (size_t i = 0; i < balls_amount_; ++i) {
            for (size_t j = 0; j < balls_amount_; ++j) {
                size_t x = offset + ball_size * (2 * i) + ball_size / 2;
                size_t y = offset + ball_size * (2 * j) + ball_size / 2;
                std::vector<std::vector<BMPImage::Pixel>> colors(ball_size, std::vector<BMPImage::Pixel>(ball_size));
                for (int32_t i2 = 0; i2 < static_cast<int32_t>(ball_size); ++i2) {
                    for (int32_t j2 = 0; j2 < static_cast<int32_t>(ball_size); ++j2) {
                        int32_t x2 = static_cast<int32_t>(i2 + x - ball_size / 2);
                        int32_t y2 = static_cast<int32_t>(j2 + y - ball_size / 2);
                        if (x2 < 0 || x2 >= static_cast<int32_t>(image.Height()) || y2 < 0 ||
                            y2 >= static_cast<int32_t>(image.Width())) {
                            continue;
                        }
                        colors[i2][j2] = image.At(x2, y2);
                    }
                }

                AddCircle(static_cast<int32_t>(x), static_cast<int32_t>(y), static_cast<int32_t>(ball_size / 2), colors,
                          blackout, result);
            }
        }
        current_size *= (2 * balls_amount_ - 1);
        current_size /= (2 * balls_amount_ - 3);
        blackout *= blackout_coef_;
        if (blackout > 1) {
            blackout = 1;
        }
    }

    image = result;
}

SpheresFilter::SpheresFilter(uint32_t amount, double threshold) {
    balls_amount_ = amount;
    threshold_ = threshold;
}

void SpheresFilter::AddCircle(int32_t x, int32_t y, int32_t radius,
                              const std::vector<std::vector<BMPImage::Pixel>>& colors, double blackout,
                              BMPImage& image) {
    int32_t width = static_cast<int32_t>(colors[0].size());
    int32_t height = static_cast<int32_t>(colors.size());
    const int32_t step = 2;
    for (int32_t i2 = 0; i2 < height; ++i2) {
        for (int32_t j2 = 0; j2 < width; ++j2) {
            int32_t i = x - height / 2 + i2;
            int32_t j = y - width / 2 + j2;
            if (i < 0 || i >= static_cast<int32_t>(image.Height()) || j < 0 ||
                j >= static_cast<int32_t>(image.Width())) {
                continue;
            }
            uint8_t r = colors[i2][j2].r;
            uint8_t g = colors[i2][j2].g;
            uint8_t b = colors[i2][j2].b;
            const double coef = 0.6;
            if ((x - i) * (x - i) + (y - j) * (y - j) < radius * radius / (step * step)) {
                uint8_t max_r = std::max(static_cast<uint8_t>(bmp::MAX_COLOR * coef), r);
                uint8_t max_g = std::max(static_cast<uint8_t>(bmp::MAX_COLOR * coef), g);
                uint8_t max_b = std::max(static_cast<uint8_t>(bmp::MAX_COLOR * coef), b);

                image.At(i, j).r = static_cast<uint8_t>(
                    std::min(static_cast<double>(max_r) - static_cast<double>(max_r - r) * 2 *
                                                              std::sqrt((x - i) * (x - i) + (y - j) * (y - j)) / radius,
                             static_cast<double>(bmp::MAX_COLOR)) *
                    blackout);
                image.At(i, j).g = static_cast<uint8_t>(
                    std::min(static_cast<double>(max_g) - static_cast<double>(max_g - g) * 2 *
                                                              std::sqrt((x - i) * (x - i) + (y - j) * (y - j)) / radius,
                             static_cast<double>(bmp::MAX_COLOR)) *
                    blackout);
                image.At(i, j).b = static_cast<uint8_t>(
                    std::min(static_cast<double>(max_b) - static_cast<double>(max_b - b) * 2 *
                                                              std::sqrt((x - i) * (x - i) + (y - j) * (y - j)) / radius,
                             static_cast<double>(bmp::MAX_COLOR)) *
                    blackout);
            } else if ((x - i) * (x - i) + (y - j) * (y - j) >= radius * radius / (step * step) &&
                       (x - i) * (x - i) + (y - j) * (y - j) <= radius * radius) {
                image.At(i, j).r = static_cast<uint8_t>(
                    (static_cast<double>(r) - ((static_cast<double>(r)) / (radius)) *
                                                  (std::sqrt((x - i) * (x - i) + (y - j) * (y - j)) - radius / step)) *
                    blackout);
                image.At(i, j).g = static_cast<uint8_t>(
                    (static_cast<double>(g) - ((static_cast<double>(g)) / (radius)) *
                                                  (std::sqrt((x - i) * (x - i) + (y - j) * (y - j)) - radius / step)) *
                    blackout);
                image.At(i, j).b = static_cast<uint8_t>(
                    (static_cast<double>(b) - ((static_cast<double>(b)) / (radius)) *
                                                  (std::sqrt((x - i) * (x - i) + (y - j) * (y - j)) - radius / step)) *
                    blackout);
            }
        }
    }
}