#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/Planet.h"

TEST_CASE("Template") {
    Planet planet;
    REQUIRE(planet.getType() == 0);
}