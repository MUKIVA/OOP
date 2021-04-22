#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN

#include "../../../Catch/catch.hpp"

#include "../HTMLDecode/Decode.h"

SCENARIO("The string can be empty")
{
	std::string str;
	REQUIRE(HtmlDecode(str) == "");
}

SCENARIO("String may not contain tags")
{
	std::string str = "Cat <says> Meow. M&M";
	REQUIRE(HtmlDecode(str) == "Cat <says> Meow. M&M");
}

SCENARIO("String may contain tags")
{
	std::string str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	REQUIRE(HtmlDecode(str) == "Cat <says> \"Meow\". M&M's");
}


SCENARIO("The string can contain the beginning of the tag")
{
	std::string str = "&";
	REQUIRE(HtmlDecode(str) == "&");
}

SCENARIO("The string can contain the beginning of the tag and tag")
{
	std::string str = "&&amp;";
	REQUIRE(HtmlDecode(str) == "&&");
}