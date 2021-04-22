#include <iostream>
#define CATCH_CONFIG_MAIN

#include "../../../Catch/catch.hpp"

#include "../PrimeNumbers/GeneratePrimeNumbersSet.h"

SCENARIO("GeneratePrimeNumbersSet: upperBound < 0")
{
	std::set<int> set;
	int upperBound = -100;
	set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 0);
}

SCENARIO("GeneratePrimeNumbersSet: upperBound = 0")
{
	std::set<int> set;
	int upperBound = 0;
	set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 0);
}

SCENARIO("GeneratePrimeNumbersSet: upperBound > 0")
{
	std::set<int> set;
	int upperBound = 40;
	set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 12);
}

SCENARIO("GeneratePrimeNumbersSet: upperBound = 100000000")
{
	std::set<int> set;
	int upperBound = 100000000;
	set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 5761455);
}

SCENARIO("GeneratePrimeNumbersSet: upperBound > 100000000")
{
	std::set<int> set;
	int upperBound = 100000100;
	set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 0);
}

SCENARIO("GeneratePrimeNumbersSet: upperBound = 4")
{
	std::set<int> set;
	int upperBound = 4;
	set = GeneratePrimeNumbersSet(upperBound);
	REQUIRE(set.size() == 2);
}