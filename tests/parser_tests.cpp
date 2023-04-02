#include <catch.hpp>
#include "Parser.h"
#include "Exceptions.h"

TEST_CASE("ParserWithoutFilters") {
    char* argv[3] = {strdup(".image_processor"), strdup("input.bmp"), strdup("output.bmp")};
    Parser parser(3, argv);
    REQUIRE((parser.input_path == "input.bmp" && parser.output_path == "output.bmp" && parser.args.empty()));
}

TEST_CASE("ParserWithoutParameters") {
    char* argv[1] = {strdup(".image_processor")};
    REQUIRE_THROWS_AS(Parser(1, argv), ManualExceptions);
}

TEST_CASE("ParserFewParameters") {
    char* argv[2] = {strdup(".image_processor"), strdup("input.bmp")};
    REQUIRE_THROWS_AS(Parser(2, argv), NumberOfParametersExceptions);
}
