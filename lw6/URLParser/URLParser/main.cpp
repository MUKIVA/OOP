#include <iostream>
#include <string>
#include <regex>
#include "CHttpUrl.h"
#include "CUrlParsingError.h"


int main()
{
	std::string urlString;
	while (std::getline(std::cin, urlString))
	{
		try
		{
			CHttpUrl url(urlString);
			std::cout << "url: " << url.GetURL() << std::endl;
			std::cout << "Protocol: " << url.GetProtocolString(url.GetProtocol()) << std::endl;
			std::cout << "Domain: " << url.GetDomain() << std::endl;
			std::cout << "Port: " << url.GetPort() << std::endl;
			std::cout << "Document: " << url.GetDocument() << std::endl;
			std::cout << std::endl;
		}
		catch (const CUrlParsingError& error)
		{
			std::cout << error.what() << std::endl;
		}
	}
	return 0;
}