#include "catch.hpp"
#include "bigexponent.h"
#include <iostream>
#include <cmath>

bool double_equals(double v1,double v2)
{
    return fabs(v1 - v2) < 0.0000001;
}

TEST_CASE("Perform big exponent","[bigexponent]")
{

    REQUIRE(double_equals(Algo::power(1280,3),pow(1280,3.0)));

    REQUIRE(double_equals(Algo::power(1.01,69),pow(1.01,69.0)));

    REQUIRE(double_equals(Algo::power(0.99 ,143),pow(0.99,143.0)));

    REQUIRE(double_equals(Algo::power(1.0001,1024),pow(1.0001,1024.0)));

}
