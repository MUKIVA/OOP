#include "ParseURL.h"
#include <regex>
#include <map>
#include <algorithm>

const int PROTOCOL_INDEX = 1;
const int HOST_INDEX = 3;
const int PORT_INDEX = 5;
const int START_DOCUMENT_INDEX = 6;
const int DOCUMENT_INDEX = 7;
const int MAX_PORT = 65535;

const std::map<std::string, Protocol> stringToProtocolMap{
	{"http", Protocol::HTTP},
	{"https", Protocol::HTTPS},
	{"ftp", Protocol::FTP}
};

const std::map<Protocol, int> defaultPortValueForProtocol{
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443},
	{Protocol::FTP, 21}
};

bool GetProtocol(std::string& protocolStr, Protocol& protocol)
{
	std::transform(protocolStr.begin(), protocolStr.end(),protocolStr.begin() , tolower);
	if (stringToProtocolMap.find(protocolStr) != stringToProtocolMap.end())
	{
		protocol = stringToProtocolMap.at(protocolStr);
		return 1;
	}
	return false;
}

bool GetPort(std::string& portStr, int& port, Protocol protocol)
{
	if (portStr.empty())
	{
		port = defaultPortValueForProtocol.at(protocol);
		return true;
	}
	port = std::stoi(portStr);
	if (port > 0 && port <= MAX_PORT)
	{
		return true;
	}
	return false;
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex urlReg("(.+)"
					  "(://)"
					  "([^/^:]+)"
					  "(:)?"
					  "(\\d{1,5})?"
					  "(/)?"
					  "(.*)?");
	std::smatch urlMatch;
	if (regex_match(url, urlMatch, urlReg))
	{
		std::string protocolStr = urlMatch[PROTOCOL_INDEX].str();
		if (!GetProtocol(protocolStr, protocol))
		{
			return false;
		}
		std::string portStr = urlMatch[PORT_INDEX].str();
		if (!GetPort(portStr, port, protocol))
		{
			return false;
		}
		if (urlMatch[START_DOCUMENT_INDEX].str().empty()
			&& !urlMatch[DOCUMENT_INDEX].str().empty())
		{
			return false;
		}
		document = urlMatch[DOCUMENT_INDEX].str();
		host = urlMatch[HOST_INDEX].str();
		return true;
	}
	return false;
}
