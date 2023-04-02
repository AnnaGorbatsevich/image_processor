#include "Reader.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include "Exceptions.h"
#include "BMP.h"

namespace get_bit {
uint32_t Get32UBit(char buffer[]) {
    return static_cast<uint32_t>(static_cast<uint8_t>(buffer[0])) |
           static_cast<uint32_t>(static_cast<uint8_t>(buffer[1])) << bmp::BITS_IN_BYTES |
           static_cast<uint32_t>(static_cast<uint8_t>(buffer[2])) << (2 * bmp::BITS_IN_BYTES) |
           static_cast<uint32_t>(static_cast<uint8_t>(buffer[3])) << (3 * bmp::BITS_IN_BYTES);
}
int32_t Get32Bit(char buffer[]) {
    return static_cast<int32_t>(static_cast<uint8_t>(buffer[0])) |
           static_cast<int32_t>(static_cast<uint8_t>(buffer[1])) << bmp::BITS_IN_BYTES |
           static_cast<int32_t>(static_cast<uint8_t>(buffer[2])) << (2 * bmp::BITS_IN_BYTES) |
           static_cast<int32_t>(static_cast<uint8_t>(buffer[3])) << (3 * bmp::BITS_IN_BYTES);
}

uint16_t Get16UBit(char buffer[]) {
    return static_cast<uint16_t>(static_cast<uint8_t>(buffer[0])) |
           static_cast<uint16_t>(static_cast<uint8_t>(buffer[1])) << bmp::BITS_IN_BYTES;
}
}  // namespace get_bit

BMPImage Reader::LoadFile(std::string_view path) {
    BMPImage result;
    std::ifstream fin;

    try {
        fin.open(static_cast<std::string>(path), std::ios::binary);
    } catch (const std::exception &e) {
        throw OpenExceptions("error opening the " + static_cast<std::string>(path) + " file, try another file");
    }
    if (!fin.is_open()) {
        throw OpenExceptions("error opening the " + static_cast<std::string>(path) + " file, try another file");
    }
    bmp::BMPFileHeader file_header;
    bmp::BMPInfoHeader bmp_info_header;
    if (!fin.read(reinterpret_cast<char *>(&file_header), sizeof(file_header))) {
        throw ReadExceptions("error reading the " + static_cast<std::string>(path) + " file, try another file");
    }
    if (file_header.file_type[0] != 'B' || file_header.file_type[1] != 'M') {
        throw NotBmpExceptions{"only bmp files are supported, try another file"};
    }
    if (!fin.read(reinterpret_cast<char *>(&bmp_info_header), sizeof(bmp_info_header))) {
        throw ReadExceptions("error reading the" + static_cast<std::string>(path) + " file, try another file");
    }

    int32_t width = get_bit::Get32Bit(reinterpret_cast<char *>(bmp_info_header.width));
    int32_t height = get_bit::Get32Bit(reinterpret_cast<char *>(bmp_info_header.height));
    uint16_t bit_count = get_bit::Get16UBit(reinterpret_cast<char *>(bmp_info_header.bit_count));
    if (bit_count != bmp::COUNT_BITS) {
        throw BitsCountExceptions{"only 24-bits files are supported, but " + static_cast<std::string>(path) + " is " +
                                  std::to_string(bit_count) + "-bits, try another file"};
    }

    uint16_t bytes_in_line = ((3 * width + 3) / 4) * 4;
    result.Resize(width, height);
    uint16_t extra_bytes = bytes_in_line - width * 3;
    result.GetHor() = get_bit::Get32UBit(reinterpret_cast<char *>(bmp_info_header.x_pixels_per_meter));
    result.GetVert() = get_bit::Get32UBit(reinterpret_cast<char *>(bmp_info_header.y_pixels_per_meter));
    int32_t begin_bytes = get_bit::Get32Bit(reinterpret_cast<char *>(file_header.offset_data));

    fin.seekg(begin_bytes - static_cast<int32_t>(sizeof(bmp::BMPInfoHeader) + sizeof(bmp::BMPFileHeader)),
              std::ios::cur);
    for (size_t i = 0; i < static_cast<size_t>(height); ++i) {
        for (size_t j = 0; j < static_cast<size_t>(width); ++j) {
            char buffer[3];
            if (!fin.read(buffer, 3)) {
                throw ReadExceptions("error reading the " + static_cast<std::string>(path) + " file, try another file");
            }
            result.At(i, j).b = buffer[0];
            result.At(i, j).g = buffer[1];
            result.At(i, j).r = buffer[2];
        }
        fin.seekg(extra_bytes, std::ios::cur);
    }
    return result;
}
