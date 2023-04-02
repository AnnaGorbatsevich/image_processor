#pragma once
#include <exception>
#include <string>

class Exception : public std::exception {
public:
    explicit Exception() = default;
    explicit Exception(std::string message);
    const char* what() const noexcept override;

    std::string message_;
};
