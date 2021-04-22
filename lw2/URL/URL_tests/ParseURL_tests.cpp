#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN

#include "../../../Catch/catch.hpp"

#include "../URL/ParseURL.h"

SCENARIO("ParseURL: protocol host doc")
{
	std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;
	ParseURL(url, protocol, port, host, document);
	REQUIRE((protocol == Protocol::HTTP
		&& port == 80
		&& host == "www.mysite.com"
		&& document == "docs/document1.html?page=30&lang=en#title"));
}

SCENARIO("ParseURL: protocol port host doc")
{
	std::string url = "http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;
	ParseURL(url, protocol, port, host, document);
	REQUIRE((protocol == Protocol::HTTP
		&& port == 100
		&& host == "www.mysite.com"
		&& document == "docs/document1.html?page=30&lang=en#title"));
}

SCENARIO("ParseURL: protocol port > MAX_PORT host doc")
{
	std::string url = "http://www.mysite.com:65537/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;
	bool res;
	res = ParseURL(url, protocol, port, host, document);
	REQUIRE(res == false);
}

SCENARIO("ParseURL: udefined_protocol port host doc")
{
	std::string url = "htt://www.mysite.com/docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;
	bool res;
	res = ParseURL(url, protocol, port, host, document);
	REQUIRE(res == false);
}

SCENARIO("ParseURL: protocol port host")
{
	std::string url = "http://www.mysite.com:100";
	std::string host, document;
	Protocol protocol;
	int port;
	ParseURL(url, protocol, port, host, document);
	REQUIRE((protocol == Protocol::HTTP
		&& port == 100
		&& host == "www.mysite.com"
		&& document == ""));
}

SCENARIO("ParseURL: empty")
{
	std::string url = "";
	std::string host, document;
	Protocol protocol;
	int port;
	bool res;
	res = ParseURL(url, protocol, port, host, document);
	REQUIRE(res == false);
}

SCENARIO("ParseURL: protocol port_start host doc")
{
	std::string url = "http://www.mysite.com:docs/document1.html?page=30&lang=en#title";
	std::string host, document;
	Protocol protocol;
	int port;
	bool res;
	res = ParseURL(url, protocol, port, host, document);
	REQUIRE(res == false);
}