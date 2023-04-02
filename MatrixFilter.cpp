#include "MatrixFilter.h"
#include "Filters.h"

MatrixFilter::MatrixFilter() = default;

void MatrixFilter::ApplyFilter(BMPImage &image) {
    uint32_t height = image.Height();
    uint32_t width = image.Width();
    std::vector<std::vector<BMPImage::Pixel>> new_data(height + 2, std::vector<BMPImage::Pixel>(width + 2));

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            new_data[i + 1][j + 1] = image.At(i, j);
        }
    }
    for (size_t i = 1; i < height + 1; ++i) {
        new_data[i][0] = new_data[i][1];
        new_data[i][width + 1] = new_data[i][width];
    }

    for (size_t j = 1; j < width + 1; ++j) {
        new_data[0][j] = new_data[1][j];
        new_data[height + 1][j] = new_data[height][j];
    }

    new_data[0][0] = new_data[1][1];
    new_data[0][width + 1] = new_data[1][width];
    new_data[height + 1][width + 1] = new_data[height][width];
    new_data[height + 1][0] = new_data[height][1];
    for (int i = 1; i < static_cast<int>(height) + 1; ++i) {
        for (int j = 1; j < static_cast<int>(width) + 1; ++j) {
            int32_t result_r = 0;
            int32_t result_g = 0;
            int32_t result_b = 0;
            for (int x = 0; x < 3; ++x) {
                for (int y = 0; y < 3; ++y) {

                    result_r += matrix_[x][y] * static_cast<int32_t>(new_data[i + x - 1][j + y - 1].r);
                    result_g += matrix_[x][y] * static_cast<int32_t>(new_data[i + x - 1][j + y - 1].g);
                    result_b += matrix_[x][y] * static_cast<int32_t>(new_data[i + x - 1][j + y - 1].b);
                }
            }
            image.At(i - 1, j - 1).r =
                static_cast<uint8_t>(std::min(static_cast<int32_t>(max_color), std::max(0, result_r)));
            image.At(i - 1, j - 1).g =
                static_cast<uint8_t>(std::min(static_cast<int32_t>(max_color), std::max(0, result_g)));
            image.At(i - 1, j - 1).b =
                static_cast<uint8_t>(std::min(static_cast<int32_t>(max_color), std::max(0, result_b)));
        }
    }
}
