#include "Writer.h"
#include "BMPImage.h"
#include "BMP.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include "Exceptions.h"

void Writer::SaveFile(std::string_view path, BMPImage &image) {
    if (path.size() < 3 || path[path.size() - 1] != 'p' || path[path.size() - 2] != 'm' ||
        path[path.size() - 3] != 'b') {
        throw NotBmpExceptions{"only bmp files are supported, try another file"};
    }
    std::ofstream fout;
    fout.open(static_cast<std::string>(path), std::ios::binary);

    uint32_t height = static_cast<uint32_t>(image.Height());

    uint32_t width = static_cast<uint32_t>(image.Width());
    uint32_t bytes_in_line = (width * 3 + 3) / 4 * 4;
    uint32_t extra_bytes = bytes_in_line - width * 3;
    char extra_zeros[] = {0, 0, 0};
    uint32_t file_size = sizeof(bmp::BMPFileHeader) + sizeof(bmp::BMPInfoHeader) + height * bytes_in_line;

    bmp::BMPFileHeader file_header;
    std::memset(&file_header, 0, sizeof(file_header));
    file_header.file_type[0] = 'B';
    file_header.file_type[1] = 'M';
    bmp::FromInt(file_header.file_size, file_size);
    bmp::FromInt(file_header.offset_data,
                 static_cast<uint32_t>(sizeof(bmp::BMPFileHeader) + sizeof(bmp::BMPInfoHeader)));

    bmp::BMPInfoHeader bmp_info_header;
    bmp::FromInt(bmp_info_header.size, static_cast<uint32_t>(sizeof(bmp_info_header)));
    bmp::FromInt(reinterpret_cast<uint8_t *>(bmp_info_header.width), static_cast<uint32_t>(width));
    bmp::FromInt(reinterpret_cast<uint8_t *>(bmp_info_header.height), static_cast<uint32_t>(height));
    bmp::FromInt(bmp_info_header.planes, static_cast<uint16_t>(1));
    bmp::FromInt(bmp_info_header.bit_count, static_cast<uint16_t>(bmp::COUNT_BITS));
    bmp::FromInt(bmp_info_header.compression, static_cast<uint32_t>(0));
    bmp::FromInt(bmp_info_header.size_image, static_cast<uint32_t>(height * width));
    bmp::FromInt(reinterpret_cast<uint8_t *>(bmp_info_header.x_pixels_per_meter), image.GetHor());
    bmp::FromInt(reinterpret_cast<uint8_t *>(bmp_info_header.y_pixels_per_meter), image.GetVert());
    bmp::FromInt(bmp_info_header.colors_used, static_cast<uint32_t>(0));
    bmp::FromInt(bmp_info_header.colors_important, static_cast<uint32_t>(0));

    if (!fout.is_open()) {
        throw OpenExceptions("error opening the " + static_cast<std::string>(path) + " file, try another file");
    }
    if (!fout.write(reinterpret_cast<const char *>(&file_header), sizeof(file_header))) {
        throw WriteExceptions("error writing to " + static_cast<std::string>(path) + " file, try another file");
    }
    if (!fout.write(reinterpret_cast<const char *>(&bmp_info_header), sizeof(bmp_info_header))) {
        throw WriteExceptions("error writing to " + static_cast<std::string>(path) + " file, try another file");
    }
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            uint8_t buffer[3] = {image.At(i, j).b, image.At(i, j).g, image.At(i, j).r};
            if (!fout.write(reinterpret_cast<const char *>(buffer), 3)) {
                throw WriteExceptions("error writing to " + static_cast<std::string>(path) + " file, try another file");
            }
        }
        if (!fout.write(extra_zeros, extra_bytes)) {
            throw WriteExceptions("error writing to " + static_cast<std::string>(path) + " file, try another file");
        }
    }
    fout.close();
}