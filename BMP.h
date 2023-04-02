#pragma once
#include <iostream>
#include <cstring>

namespace bmp {

const uint8_t MAX_COLOR = 255;
const uint8_t BITS_IN_BYTES = 8;
const uint16_t COUNT_BITS = 24;

template <typename T>
static void FromInt(uint8_t *ptr, T value) {
    std::memcpy(ptr, &value, sizeof(value));
}
#pragma pack(push, 1)
struct BMPFileHeader {
    uint8_t file_type[2];
    uint8_t file_size[4];
    uint8_t reserved1[2];
    uint8_t reserved2[2];
    uint8_t offset_data[4];
};

struct BMPInfoHeader {
    uint8_t size[4];
    int8_t width[4];
    int8_t height[4];
    uint8_t planes[2];
    uint8_t bit_count[2];
    uint8_t compression[4];
    uint8_t size_image[4];
    int8_t x_pixels_per_meter[4];
    int8_t y_pixels_per_meter[4];
    uint8_t colors_used[4];
    uint8_t colors_important[4];
};
#pragma pack(pop)

}  // namespace bmp
