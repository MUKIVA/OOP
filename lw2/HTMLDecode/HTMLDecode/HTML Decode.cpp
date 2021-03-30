#include <iostream>
#include <iterator>
#include <string>
#include "Decode.h"

int main()
{
	std::cout << "Enter the string to decode:\n";
	std::string strToDecode;
	std::getline(std::cin, strToDecode);
	std::cout << HtmlDecode(strToDecode) << std::endl;
}
