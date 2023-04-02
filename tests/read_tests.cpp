#include <catch.hpp>
#include "Reader.h"
#include "Exceptions.h"

TEST_CASE("NotExistentFile") {
    Reader reader;
    REQUIRE_THROWS_AS(reader.LoadFile("sth.bmp"), OpenExceptions);
}

TEST_CASE("NotBMPFile") {
    Reader reader;
    REQUIRE_THROWS(reader.LoadFile("read_tests.cpp"));
}