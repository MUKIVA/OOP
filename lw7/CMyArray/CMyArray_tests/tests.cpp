#define CATCH_CONFIG_MAIN

#include <string>

#include "../../../Catch/catch.hpp"
#include "../CMyArray/CMyArray.h"

SCENARIO("Constructor tests with empty array")
{
	WHEN("default constructor")
	{
		CMyArray<double> arr;
		CMyArray<std::string> sArr;
		REQUIRE_THROWS(arr.GetBack());
		REQUIRE(arr.GetSize() == 0);
		REQUIRE(arr.GetCapacity() == 0);
		REQUIRE_THROWS(sArr.GetBack());
		REQUIRE(sArr.GetSize() == 0);
		REQUIRE(sArr.GetCapacity() == 0);
	}

	WHEN("copy constructor")
	{
		CMyArray<double> arr;
		CMyArray<std::string> sArr;
		REQUIRE_THROWS(arr.GetBack());
		REQUIRE(arr.GetSize() == 0);
		REQUIRE(arr.GetCapacity() == 0);
		REQUIRE_THROWS(sArr.GetBack());
		REQUIRE(sArr.GetSize() == 0);
		REQUIRE(sArr.GetCapacity() == 0);

		CMyArray<double> arr2(arr);
		CMyArray<std::string> sArr2(sArr);
		REQUIRE_THROWS(arr2.GetBack());
		REQUIRE(arr2.GetSize() == 0);
		REQUIRE(arr2.GetCapacity() == 0);
		REQUIRE_FALSE(arr.begin() != arr2.begin());
		REQUIRE_FALSE(arr.end() != arr2.end());
		REQUIRE_THROWS(sArr.GetBack());
		REQUIRE(sArr.GetSize() == 0);
		REQUIRE(sArr.GetCapacity() == 0);
		REQUIRE_FALSE(sArr.begin() != sArr2.begin());
		REQUIRE_FALSE(sArr.end() != sArr2.end());
	}

	WHEN("move constructor")
	{
		CMyArray<double> arr;
		CMyArray<std::string> sArr;
		REQUIRE_THROWS(arr.GetBack());
		REQUIRE(arr.GetSize() == 0);
		REQUIRE(arr.GetCapacity() == 0);
		REQUIRE_THROWS(sArr.GetBack());
		REQUIRE(sArr.GetSize() == 0);
		REQUIRE(sArr.GetCapacity() == 0);

		CMyArray<double> arr2(std::move(arr));
		CMyArray<std::string> sArr2(std::move(sArr));
		REQUIRE_THROWS(arr2.GetBack());
		REQUIRE(arr2.GetSize() == 0);
		REQUIRE(arr2.GetCapacity() == 0);
		REQUIRE_FALSE(arr.begin() != arr2.begin());
		REQUIRE_FALSE(arr.end() != arr2.end());
		REQUIRE_THROWS(sArr.GetBack());
		REQUIRE(sArr.GetSize() == 0);
		REQUIRE(sArr.GetCapacity() == 0);
		REQUIRE_FALSE(sArr.begin() != sArr2.begin());
		REQUIRE_FALSE(sArr.end() != sArr2.end());
	}
}

SCENARIO("The array can be filled")
{
	GIVEN("empty array")
	{
		CMyArray<double> arr;
		CMyArray<std::string> sArr;
		arr.Append(10);
		sArr.Append("hello");
		REQUIRE(arr.GetSize() == 1);
		REQUIRE(sArr.GetSize() == 1);
		REQUIRE(arr.GetBack() == 10);
		REQUIRE(sArr.GetBack() == "hello");
	}
	CMyArray<double> arr;
	CMyArray<std::string> sArr;

	arr.Append(10);
	arr.Append(20);
	arr.Append(30);

	sArr.Append("hello");

	GIVEN("filled array")
	{
		arr.Append(40);
		sArr.Append("world");
		REQUIRE(arr.GetSize() == 4);
		REQUIRE(sArr.GetSize() == 2);
		REQUIRE(arr.GetBack() == 40);
		REQUIRE(sArr.GetBack() == "world");
	}
}

SCENARIO("Array can be cleared")
{
	WHEN("empty array")
	{
		CMyArray<double> arr;
		CMyArray<std::string> sArr;

		arr.Clear();
		sArr.Clear();

		REQUIRE_THROWS(arr.GetBack());
		REQUIRE(arr.GetSize() == 0);
		REQUIRE(arr.GetCapacity() == 0);
		REQUIRE_THROWS(sArr.GetBack());
		REQUIRE(sArr.GetSize() == 0);
		REQUIRE(sArr.GetCapacity() == 0);
	}

	WHEN("filled array")
	{
		CMyArray<double> arr;
		CMyArray<std::string> sArr;

		arr.Append(10);
		arr.Append(20);
		arr.Append(30);

		sArr.Append("hello");

		arr.Clear();
		sArr.Clear();

		REQUIRE_THROWS(arr.GetBack());
		REQUIRE(arr.GetSize() == 0);
		REQUIRE(arr.GetCapacity() == 0);
		REQUIRE_THROWS(sArr.GetBack());
		REQUIRE(sArr.GetSize() == 0);
		REQUIRE(sArr.GetCapacity() == 0);
	}
}

SCENARIO("filled array constructor tests")
{
	CMyArray<double> arr;
	CMyArray<std::string> sArr;

	arr.Append(10);
	arr.Append(20);
	arr.Append(30);

	sArr.Append("hello");

	WHEN("copy constructor")
	{
		CMyArray<double> arr2(arr);
		CMyArray<std::string> sArr2(sArr);
		REQUIRE(arr2.GetSize() == 3);
		REQUIRE(sArr2.GetSize() == 1);
		REQUIRE(arr2.GetBack() == 30);
		REQUIRE(sArr2.GetBack() == "hello");
		REQUIRE(arr.begin() != arr2.begin());
		REQUIRE(sArr.begin() != sArr2.begin());
	}

	WHEN("move constructor")
	{
		auto arrBegin = arr.begin();
		auto sArrBegin = sArr.begin();
		CMyArray<double> arr2(std::move(arr));
		CMyArray<std::string> sArr2(std::move(sArr));
		REQUIRE(arr2.GetSize() == 3);
		REQUIRE(sArr2.GetSize() == 1);
		REQUIRE(arr2.GetBack() == 30);
		REQUIRE(sArr2.GetBack() == "hello");
		REQUIRE_FALSE(arrBegin != arr2.begin());
		REQUIRE_FALSE(sArrBegin != sArr2.begin());
	}
}

SCENARIO("operator[] tests")
{
	GIVEN("empty array")
	{
		CMyArray<double> arr;
		CMyArray<std::string> sArr;

		REQUIRE_THROWS(arr[0]);
		REQUIRE_THROWS(arr[-1]);
		REQUIRE_THROWS(arr[1]);
		REQUIRE_THROWS(sArr[0]);
		REQUIRE_THROWS(sArr[-1]);
		REQUIRE_THROWS(sArr[1]);
	}

	GIVEN("filled array")
	{
		CMyArray<double> arr;
		CMyArray<std::string> sArr;

		arr.Append(10);
		arr.Append(20);
		arr.Append(30);

		sArr.Append("hello");

		REQUIRE_THROWS(arr[-1]);
		REQUIRE(arr[0] == 10);
		REQUIRE(arr[1] == 20);
		REQUIRE(arr[2] == 30);
		REQUIRE_THROWS(arr[3]);

		REQUIRE_THROWS(sArr[-1]);
		REQUIRE(sArr[0] == "hello");
		REQUIRE_THROWS(sArr[1]);
	}
}

SCENARIO("array can be resized")
{
	GIVEN("empty array")
	{

	}
}