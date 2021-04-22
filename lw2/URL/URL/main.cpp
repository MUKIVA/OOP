#include <iostream>
#include "windows.h"
#include "ParseURL.h"
#include <regex>
#include <string>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string host, url, document;
	int port;
	Protocol protocol;
	while (std::getline(std::cin, url))
	{
		if (ParseURL(url, protocol, port, host, document))
		{
			std::cout << url << std::endl
					  << "HOST: " << host << std::endl
					  << "PORT: " << port << std::endl
					  << "DOC: " << document << std::endl;
		}
	}
	return 0;
}