#include <iostream>
#include <string>
#include "CHttpUrl.h"


int main()
{
	std::string urlString;
	while (std::getline(std::cin, urlString))
	{
		CHttpUrl url(urlString);
		std::cout << "url: " << url.GetURL() << std::endl;
		std::cout << "Protocol: " << url.GetProtocolString(url.GetProtocol()) << std::endl;
		std::cout << "Domain: " << url.GetDomain() << std::endl;
		std::cout << "Port: " << url.GetPort() << std::endl;
		std::cout << "Document: " << url.GetDocument() << std::endl;
		std::cout << std::endl;
	}
	return 0;
}