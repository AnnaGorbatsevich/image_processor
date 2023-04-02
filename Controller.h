#pragma once
#include "BMPImage.h"

class Controller {
public:
    Controller() = default;
    Controller(BMPImage image, std::vector<std::string> filters);

    bool ApplyFilters();

    BMPImage GetImage();

private:
    BMPImage image_;
    std::vector<std::string> filters_;
};
