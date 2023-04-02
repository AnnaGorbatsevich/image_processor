#include "Controller.h"
#include "GsFilter.h"
#include "CropFilter.h"
#include "NegFilter.h"
#include "BlurFilter.h"
#include "SharpFilter.h"
#include "Exceptions.h"
#include "SpheresFilter.h"
#include <memory>

Controller::Controller(BMPImage image, std::vector<std::string> filters) {
    image_ = image;
    filters_ = filters;
}

bool Controller::ApplyFilters() {
    for (size_t i = 0; i < filters_.size(); ++i) {
        std::unique_ptr<Filter> current_filter;
        if (filters_[i] == "-crop") {
            if (i + 2 >= filters_.size()) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i]);
            }
            int64_t w = 0;
            int64_t h = 0;
            try {
                w = std::stoi(filters_[i + 1]);
                h = std::stoi(filters_[i + 2]);
            } catch (const std::exception& e) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i]);
            }
            if (w <= 0 || h <= 0) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i]);
            }
            current_filter = std::make_unique<CropFilter>(w, h);

            i += 2;
        } else if (filters_[i] == "-gs") {
            current_filter = std::make_unique<GsFilter>();
        } else if (filters_[i] == "-neg") {
            current_filter = std::make_unique<NegFilter>();
        } else if (filters_[i] == "-sharp") {
            current_filter = std::make_unique<SharpFilter>();
        } else if (filters_[i] == "-edge") {
            if (i + 1 >= filters_.size()) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i]);
            }
            double threshold = 0.0;
            try {
                threshold = std::stof(filters_[i + 1]);
            } catch (const std::exception& e) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i]);
            }
            current_filter = std::make_unique<EdgeFilter>(threshold);
            ++i;
        } else if (filters_[i] == "-blur") {
            if (i + 1 >= filters_.size()) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i]);
            }

            double sigma = 0.0;
            try {
                sigma = std::stof(filters_[i + 1]);
            } catch (const std::exception& e) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i]);
            }
            current_filter = std::make_unique<BlurFilter>(sigma);
            ++i;
        } else if (filters_[i] == "-spheres") {
            if (i + 2 >= filters_.size()) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i]);
            }
            uint32_t amount = 0;
            double threshold = 0.0;
            try {
                amount = std::stoi(filters_[i + 1]);
            } catch (const std::exception& e) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i] +
                                                 ", amount must be integer");
            }
            try {
                threshold = std::stof(filters_[i + 2]);
            } catch (const std::exception& e) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i] +
                                                 ", threshold must be float");
            }
            if (amount < 2) {
                throw FilterParametersExceptions("incorrect parameters for the filter: " + filters_[i] +
                                                 ", amount must be >= 2");
            }
            current_filter = std::make_unique<SpheresFilter>(amount, threshold);
            i += 2;
        } else {
            throw FilterNamesExceptions("incorrect filter name: " + filters_[i]);
        }
        try {
            current_filter->ApplyFilter(image_);
        } catch (const std::exception& e) {
            throw;
        }
    }
    return true;
}

BMPImage Controller::GetImage() {
    return image_;
}