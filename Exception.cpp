#include "Exception.h"

Exception::Exception(std::string message) {
    message_ = message;
}
const char* Exception::what() const noexcept {
    return message_.c_str();
}
