#pragma once
#include <vector>
#include <string>

class Parser {
public:
    Parser() = default;
    Parser(int argc, char** argv);
    std::string_view input_path;
    std::string_view output_path;
    std::vector<std::string> args;
};
