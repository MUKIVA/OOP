#include <iostream>
#define CATCH_CONFIG_MAIN

#include "../../../Catch/catch.hpp"

#include "../vector/MultiplyByMinimum.h"

SCENARIO("A vector without items")
{
		FloatVector v (0);
		FloatVector emptyV(0);
		REQUIRE(v.size() == 0);
		REQUIRE(emptyV.size() == 0);
		REQUIRE(MultiplyByMinimum(v) == emptyV);
}

SCENARIO("A vector with one item")
{
	FloatVector v {10};
	FloatVector resultV {100};
	REQUIRE(MultiplyByMinimum(v) == resultV);
}

SCENARIO("A vector with some of the same items ")
{
	FloatVector v{ 10, 10, 10 };
	FloatVector resultV{ 100, 100, 100 };
	REQUIRE(MultiplyByMinimum(v) == resultV);
}

SCENARIO("A vector with some different items")
{
	FloatVector v{ 20, 10, 30 };
	FloatVector resultV{ 200, 100, 300 };
	REQUIRE(MultiplyByMinimum(v) == resultV);
}