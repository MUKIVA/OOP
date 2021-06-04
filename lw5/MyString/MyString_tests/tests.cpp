#define CATCH_CONFIG_MAIN

#include "../../../Catch/catch.hpp"

#include "../MyString/CMyString.h"
#include <string>
#include <algorithm>

SCENARIO("Constructors tests")
{
	WHEN("Empty constructor")
	{
		CMyString str;
		REQUIRE((str.GetLength() == 0));
	}

	WHEN("char*")
	{
		char* cstr = new char[5] {'T', 'E', 'S', 'T', '\0'};
		CMyString str(cstr);
		REQUIRE((str.GetLength() == 4));
		REQUIRE(std::string(str.GetStringData()) == "TEST");
	}

	WHEN("stlString")
	{
		std::string stlstr("TEST");
		CMyString str(stlstr);
		REQUIRE((str.GetLength() == 4));
		REQUIRE(std::string(str.GetStringData()) == "TEST");
	}

	WHEN("char* length")
	{
		char* cstr = new char[10]{ 'T', 'E', 'S', 'T', '\0', 'T', 'S', 'E', 'T', '\0' };
		CMyString str(cstr, 7);
		REQUIRE((str.GetLength() == 7));
		REQUIRE(std::string(str.GetStringData()) == "TEST\0TS");
	}

	WHEN("char* length")
	{
		char* cstr = new char[5]{ 'T', 'E', 'S', 'T', '\0'};
		CMyString str(cstr, 7);
		REQUIRE((str.GetLength() == 7));
		REQUIRE(std::string(str.GetStringData()) == "TEST\0  ");
	}

	WHEN("CMyString")
	{
		CMyString otherStr("TEST");
		CMyString str(otherStr);
		REQUIRE((str.GetLength() == 4));
		REQUIRE(std::string(str.GetStringData()) == "TEST");
	}

	WHEN("CMyString&&")
	{
		CMyString otherStr("TEST");
		CMyString str((CMyString&&)otherStr);
		REQUIRE((str.GetLength() == 4));
		REQUIRE(std::string(str.GetStringData()) == "TEST");
	}
}

SCENARIO("Clear test")
{
	CMyString str("TEST");
	REQUIRE(str.GetLength() == 4);
	REQUIRE(std::string(str.GetStringData()) == "TEST");
	str.Clear();
	REQUIRE((str.GetLength() == 0));
}

SCENARIO("SubString test")
{
	CMyString otherStr("TEST");
	CMyString str(otherStr.SubString(0, 3));
	REQUIRE(str.GetLength() == 3);
	REQUIRE(std::string(str.GetStringData()) == "TES");
}

SCENARIO("Boolean operator tests")
{
	WHEN("Operator ==")
	{
		CMyString str("TEST");
		THEN("CMyString && char*")
		{
			REQUIRE(str == "TEST");
			REQUIRE_FALSE(str == "asdasd");
		}

		THEN("char* && CMyString")
		{
			REQUIRE("TEST" == str);
			REQUIRE_FALSE("asdasd" == str);
		}
	}

	WHEN("Operator !=")
	{
		CMyString str("TEST");
		THEN("CMyString && char*")
		{
			REQUIRE_FALSE(str != "TEST");
			REQUIRE(str != "asdasd");
		}

		THEN("char* && CMyString")
		{
			REQUIRE_FALSE("TEST" != str);
			REQUIRE("asdasd" != str);
		}
	}

	WHEN("Operator >")
	{
		CMyString str("ABC");
		THEN("CMyString && char*")
		{
			REQUIRE(str > "A");
			REQUIRE_FALSE(str > "ABZ");
		}

		THEN("char* && CMyString")
		{
			REQUIRE_FALSE("A" > str);
			REQUIRE("ABZ" > str);
		}
	}

	WHEN("Operator <=")
	{
		CMyString str("ABC");
		THEN("CMyString && char*")
		{
			REQUIRE_FALSE(str <= "A");
			REQUIRE(str <= "ABZ");
		}

		THEN("char* && CMyString")
		{
			REQUIRE("A" <= str);
			REQUIRE_FALSE("ABZ" <= str);
		}
	}

	WHEN("Operator <")
	{
		CMyString str("ABC");
		THEN("CMyString && char*")
		{
			REQUIRE_FALSE(str < "A");
			REQUIRE(str < "ABZ");
		}

		THEN("char* && CMyString")
		{
			REQUIRE("A" < str);
			REQUIRE_FALSE("ABZ" < str);
		}
	}

	WHEN("Operator >=")
	{
		CMyString str("ABC");
		THEN("CMyString && char*")
		{
			REQUIRE(str >= "A");
			REQUIRE_FALSE(str >= "ABZ");
		}

		THEN("char* && CMyString")
		{
			REQUIRE_FALSE("A" >= str);
			REQUIRE("ABZ" >= str);
		}
	}
}

SCENARIO("I/O operator tests")
{
	GIVEN("Empty string")
	{
		CMyString str;
		WHEN("<<")
		{
			std::ostringstream oss;
			oss << str;
			REQUIRE(oss.str().empty());
		}
		WHEN(">>")
		{
			std::istringstream iss("ABOBA");
			iss >> str;
			REQUIRE(str == "ABOBA");
		}
	}

	GIVEN("Not empty string")
	{
		CMyString str("ABOBA");
		WHEN("<<")
		{
			std::ostringstream oss;
			oss << str;
			REQUIRE(oss.str() == "ABOBA");
		}
		WHEN(">>")
		{
			std::istringstream iss("A");
			iss >> str;
			REQUIRE(str == "A");
		}
	}

	GIVEN("string[>50]")
	{
		CMyString str;
		WHEN("<<")
		{
			std::ostringstream oss;
			oss << str;
			REQUIRE(oss.str().empty());
		}
		WHEN(">>")
		{
			std::istringstream iss("012345678901234567890123456789012345678901234567890123456789");
			iss >> str;
			REQUIRE(str == "012345678901234567890123456789012345678901234567890123456789");
		}
	}
}

SCENARIO("operator=")
{
	CMyString str;
	WHEN("CMyString && char*")
	{
		str = "TEST";
		REQUIRE(str == "TEST");
	}

	WHEN("CMyString && CMyString")
	{
		str = CMyString("Test");
		REQUIRE(str == "Test");
	}

	WHEN("CMyString && std::string")
	{
		str = std::string("Test");
		REQUIRE(str == "Test");
	}

	WHEN("CMyString && &&std::string")
	{
		str = std::string("Test").substr(0, 2);
		REQUIRE(str == "Te");
	}

	WHEN("CMyString s=s ")
	{
		str = "TEST";
		str = str;
		REQUIRE(str == "TEST");
	}
}

SCENARIO("operator + , +=")
{
	CMyString str;
	WHEN("str + \"\"")
	{
		str = str + "";
		REQUIRE(str == "");
	}

	WHEN("str + TEST")
	{
		str = str + "TEST";
		REQUIRE(str == "TEST");
	}

	WHEN("str + TEST + OTHER")
	{
		str = str + "TEST" + "OTHER";
		REQUIRE(str == "TESTOTHER");
	}

	WHEN("str += TEST")
	{
		str += "TEST";
		REQUIRE(str == "TEST");
	}

	WHEN("str += TEST += TEST")
	{
		str += "TEST";
		str += "TEST";
		REQUIRE(str == "TESTTEST");
	}
}

SCENARIO("stl function")
{
	CMyString str("TEST");
	WHEN("sort begin end")
	{
		std::sort(str.begin(), str.end());
		REQUIRE(str == "ESTT");
	}

	WHEN("sort rbegin rend")
	{
		std::string s("TEST");
		std::sort(s.rbegin(), s.rend());
		std::sort(str.rbegin(), str.rend());
		REQUIRE(str == s);
	}

	WHEN("fill begin end")
	{
		std::fill(str.begin(), str.end(), 'A');
		REQUIRE(str == "AAAA");
	}

	WHEN("copy const begin const end")
	{
		const auto b = str.begin();
		const auto e = str.begin();
		auto const rb = str.rbegin();
		const auto re = str.rend();
	}

}

SCENARIO("operator []")
{
	GIVEN("empty")
	{
		CMyString str;
		REQUIRE(str[0] == '\0');
		REQUIRE_THROWS(str[1]);
		REQUIRE_THROWS(str[-1]);
	}
}

SCENARIO("Iterator arithmetic")
{
	CMyString str("TEST");
	auto it = str.begin();

	WHEN("[]")
	{
		REQUIRE(it[1] == 'E');
	}

	WHEN("+")
	{
		REQUIRE((*(it + 1) == 'E'));
		REQUIRE((*(1 + it) == 'E'));
	}

	WHEN("-")
	{
		REQUIRE(str.end() - str.begin() == str.GetLength());
	}

	REQUIRE(str.begin() < str.end());
	REQUIRE(str.begin() <= str.end());
	REQUIRE(str.begin() == str.begin());
	REQUIRE_FALSE(str.begin() > str.end());
	REQUIRE_FALSE(str.begin() >= str.end());
}