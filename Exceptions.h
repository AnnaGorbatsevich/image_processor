#pragma once
#include "Exception.h"

class ManualExceptions : public Exception {
public:
    explicit ManualExceptions(std::string message) : Exception(message){};
};

class NumberOfParametersExceptions : public Exception {
public:
    explicit NumberOfParametersExceptions(std::string message) : Exception(message){};
};

class FilterNamesExceptions : public Exception {
public:
    explicit FilterNamesExceptions(std::string message) : Exception(message){};
};

class FilterParametersExceptions : public Exception {
public:
    explicit FilterParametersExceptions(std::string message) : Exception(message){};
};

class NotBmpExceptions : public Exception {
public:
    explicit NotBmpExceptions(std::string message) : Exception(message){};
};

class BitsCountExceptions : public Exception {
public:
    explicit BitsCountExceptions(std::string message) : Exception(message){};
};

class OpenExceptions : public Exception {
public:
    explicit OpenExceptions(std::string message) : Exception(message){};
};

class ReadExceptions : public Exception {
public:
    explicit ReadExceptions(std::string message) : Exception(message){};
};

class WriteExceptions : public Exception {
public:
    explicit WriteExceptions(std::string message) : Exception(message){};
};