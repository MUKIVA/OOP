#define CATCH_CONFIG_MAIN

#include "../../../Catch/catch.hpp"

#include "../URLParser/CHttpUrl.h"

SCENARIO("Constructors tests")
{
	WHEN("one argument constructor")
	{
		THEN("[Protocol]://[domain]/[document]")
		{
			CHttpUrl url("http://google.com/index.php");
			REQUIRE(url.GetDocument() == "/index.php");
			REQUIRE(url.GetDomain() == "google.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetURL() == "http://google.com/index.php");
		}

		THEN("[Protocol]://[domain]:[port]/[document]")
		{
			CHttpUrl url("http://google.com:90/index.php");
			REQUIRE(url.GetDocument() == "/index.php");
			REQUIRE(url.GetDomain() == "google.com");
			REQUIRE(url.GetPort() == 90);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetURL() == "http://google.com:90/index.php");
		}

		THEN("[Protocol]://[domain]:[port]")
		{
			CHttpUrl url("http://google.com:90");
			REQUIRE(url.GetDocument() == "");
			REQUIRE(url.GetDomain() == "google.com");
			REQUIRE(url.GetPort() == 90);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetURL() == "http://google.com:90");
		}

		THEN("[Protocol_invalid]://[domain]:[port]")
		{
			REQUIRE_THROWS(CHttpUrl("htttp://google.com:90"));
		}

		THEN("[Protocol]://[domain]:[port_invalid]")
		{
			REQUIRE_THROWS(CHttpUrl("https://google.com:!23"));
		}

		THEN("[Protocol]://[domain_invalid]:[port]")
		{
			REQUIRE_THROWS(CHttpUrl("http://:90"));
		}

		THEN("[Protocol]://[domain]:[port_invalid]")
		{
			REQUIRE_THROWS(CHttpUrl("http://google.com:0"));
		}

		THEN("[Protocol]://[domain]:[port_out_of_range]")
		{
			REQUIRE_THROWS(CHttpUrl("http://google.com:56090123123"));
		}
	}

	WHEN("Protocol, domain, document")
	{
		THEN("[Protocol][domain][document]")
		{
			CHttpUrl url("google.com", "/index.php", Protocol::HTTP);
			REQUIRE(url.GetDocument() == "/index.php");
			REQUIRE(url.GetDomain() == "google.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetURL() == "http://google.com/index.php");
		}

		THEN("[Protocol][domain_invalid][document]")
		{
			REQUIRE_THROWS(CHttpUrl("", "/index.php", Protocol::HTTP));
		}

		THEN("[Protocol][domain][document_empty]")
		{
			CHttpUrl url("google.com", "", Protocol::HTTP);
			REQUIRE(url.GetDocument() == "");
			REQUIRE(url.GetDomain() == "google.com");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetURL() == "http://google.com");
		}
	}

	WHEN("Protocol, domain, document, port")
	{
		THEN("[Protocol][domain][document][port]")
		{
			CHttpUrl url("google.com", "index.php", Protocol::HTTP, 100);
			REQUIRE(url.GetDocument() == "/index.php");
			REQUIRE(url.GetDomain() == "google.com");
			REQUIRE(url.GetPort() == 100);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetURL() == "http://google.com:100/index.php");
		}

		THEN("[Protocol][domain_invalid][document][port]")
		{
			REQUIRE_THROWS(CHttpUrl("", "index.php", Protocol::HTTP, 100));
		}

		THEN("[Protocol][domain][document_empty][port]")
		{
			CHttpUrl url("google.com", "", Protocol::HTTP, 100);
			REQUIRE(url.GetDocument() == "");
			REQUIRE(url.GetDomain() == "google.com");
			REQUIRE(url.GetPort() == 100);
			REQUIRE(url.GetProtocol() == Protocol::HTTP);
			REQUIRE(url.GetURL() == "http://google.com:100");
		}

		THEN("[Protocol][domain][document][port_invalid]")
		{
			REQUIRE_THROWS(CHttpUrl("google.com", "index.php", Protocol::HTTP, 0));
		}
	}
}

SCENARIO("port out of range")
{
	WHEN("port 65535")
	{
		CHttpUrl url("http://google.com:65535");
		REQUIRE(url.GetDocument() == "");
		REQUIRE(url.GetDomain() == "google.com");
		REQUIRE(url.GetPort() == 65535);
		REQUIRE(url.GetProtocol() == Protocol::HTTP);
		REQUIRE(url.GetURL() == "http://google.com:65535");
	}

	WHEN("port 65536")
	{
		REQUIRE_THROWS(CHttpUrl("http://google.com:65537"));
	}

	WHEN("port 0")
	{
		REQUIRE_THROWS(CHttpUrl("google.com", "index.php", Protocol::HTTP, 0));
		REQUIRE_THROWS(CHttpUrl("http://google.com:0"));
	}
}

SCENARIO("protocol tolower")
{

	CHttpUrl url("HTTP://google.com/index.php");
	REQUIRE(url.GetDocument() == "/index.php");
	REQUIRE(url.GetDomain() == "google.com");
	REQUIRE(url.GetPort() == 80);
	REQUIRE(url.GetProtocol() == Protocol::HTTP);
	REQUIRE(url.GetURL() == "http://google.com/index.php");
}