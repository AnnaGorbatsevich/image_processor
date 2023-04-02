#include "BlurFilter.h"
#include "math.h"

BlurFilter::BlurFilter(double sigma) {
    step_ = static_cast<int32_t>(sigma * 3) + 1;
    sigma_ = sigma;
    multiplier_.resize(step_);
    for (int32_t x = 0; x < step_; ++x) {
        multiplier_[x] =
            std::exp(-static_cast<double>(x * x) / sigma_ / sigma_ / 2) / std::sqrt(sigma_ * sigma_ * 2 * M_PI);
    }
}

void BlurFilter::ApplyFilter(BMPImage& image) {
    uint32_t height = image.Height();
    uint32_t width = image.Width();
    std::vector<std::vector<BMPImage::Pixel>> new_data(height, std::vector<BMPImage::Pixel>(width));
    for (int j = 0; j < static_cast<int>(width); ++j) {
        std::vector<double> r(height, 0.0);
        std::vector<double> g(height, 0.0);
        std::vector<double> b(height, 0.0);
        for (int i = 0; i < static_cast<int>(height); ++i) {
            for (int y = j - step_ + 1; y < j + step_; ++y) {
                if (y < 0) {
                    r[i] += (static_cast<double>(image.At(i, 0).r) * multiplier_[abs(y - j)]);
                    g[i] += (static_cast<double>(image.At(i, 0).g) * multiplier_[abs(y - j)]);
                    b[i] += (static_cast<double>(image.At(i, 0).b) * multiplier_[abs(y - j)]);
                } else if (y >= static_cast<int>(width)) {
                    r[i] += (static_cast<double>(image.At(i, static_cast<int>(width) - 1).r) * multiplier_[abs(y - j)]);
                    g[i] += (static_cast<double>(image.At(i, static_cast<int>(width) - 1).g) * multiplier_[abs(y - j)]);
                    b[i] += (static_cast<double>(image.At(i, static_cast<int>(width) - 1).b) * multiplier_[abs(y - j)]);
                } else {
                    r[i] += (static_cast<double>(image.At(i, y).r) * multiplier_[abs(y - j)]);
                    g[i] += (static_cast<double>(image.At(i, y).g) * multiplier_[abs(y - j)]);
                    b[i] += (static_cast<double>(image.At(i, y).b) * multiplier_[abs(y - j)]);
                }
            }
        }
        for (int i = 0; i < static_cast<int>(height); ++i) {
            double r2 = 0.0;
            double g2 = 0.0;
            double b2 = 0.0;
            for (int x = i - step_ + 1; x < i + step_; ++x) {
                if (x < 0) {
                    r2 += r[0] * multiplier_[abs(x - i)];
                    g2 += g[0] * multiplier_[abs(x - i)];
                    b2 += b[0] * multiplier_[abs(x - i)];
                } else if (x >= static_cast<int>(height)) {
                    r2 += r[static_cast<int>(height) - 1] * multiplier_[abs(x - i)];
                    g2 += g[static_cast<int>(height) - 1] * multiplier_[abs(x - i)];
                    b2 += b[static_cast<int>(height) - 1] * multiplier_[abs(x - i)];
                } else {
                    r2 += r[x] * multiplier_[abs(x - i)];
                    g2 += g[x] * multiplier_[abs(x - i)];
                    b2 += b[x] * multiplier_[abs(x - i)];
                }
            }
            new_data[i][j].r = static_cast<uint8_t>(r2);
            new_data[i][j].g = static_cast<uint8_t>(g2);
            new_data[i][j].b = static_cast<uint8_t>(b2);
        }
    }
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image.At(i, j) = new_data[i][j];
        }
    }
}