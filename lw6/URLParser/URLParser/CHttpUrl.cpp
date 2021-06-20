#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <regex>
#include <map>
#include <algorithm>



const std::map<std::string, Protocol> stringToProtocolMap{
	{ "http", Protocol::HTTP },
	{ "https", Protocol::HTTPS }
};

const std::map<Protocol, unsigned short> defaultPortValueForProtocol{
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 }
};

bool IsValidProtocol(std::string const& protocol) 
{
	return (stringToProtocolMap.find(protocol) != stringToProtocolMap.end());
}

bool IsValidDomain(std::string const& domain) 
{
	return !(domain.empty());
}

bool IsValidPort(const unsigned int port) 
{
	return port > 0 && port <= 65535;
}

std::string ConvertToDocument(std::string& document)
{
	if (document.empty())
	{
		return document;
	}

	if (document[0] != '/')
	{
		return "/" + document;
	}
	return document;
}

unsigned short ConvertToPort(std::string& port) 
{
	unsigned int result = stoi(port);
	if (!IsValidPort(result))
		throw CUrlParsingError("invalid port");
	return result;
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::regex urlReg("(.+)"
					  "(://)"
					  "([^/^:]+)"
					  "((:)(\\d+))?"
					  "((/)(.*))?");

	const unsigned short PROTOCOL_INDEX = 1;
	const unsigned short HOST_INDEX = 3;
	const unsigned short PORT_INDEX = 6;
	const unsigned short START_DOCUMENT_INDEX = 7;
	const unsigned short DOCUMENT_INDEX = 9;
	std::smatch urlMatch;
	if (regex_match(url, urlMatch, urlReg))
	{
		std::string protocol = urlMatch[PROTOCOL_INDEX].str();
		std::transform(protocol.begin(), protocol.end(), protocol.begin(), tolower);
		std::string domain = urlMatch[HOST_INDEX].str();
		std::string port = urlMatch[PORT_INDEX].matched ? urlMatch[PORT_INDEX].str() : "";
		std::string document = urlMatch[DOCUMENT_INDEX].str();

		if (!IsValidProtocol(protocol))
		{
			throw CUrlParsingError("invalid protocol");
		}

		if (!IsValidDomain(domain))
		{
			throw CUrlParsingError("invalid domain");
		}

		m_protocol = stringToProtocolMap.at(protocol);
		m_domain = domain;
		m_port = !port.empty()
			? ConvertToPort(port)
			: defaultPortValueForProtocol.at(m_protocol);
		m_document = ConvertToDocument(document);
		return;
	}
	throw CUrlParsingError("invalid url");
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_protocol(protocol)
	, m_domain(domain)
	, m_port(port)
	, m_document(document)
{
	if (!IsValidDomain(domain))
	{
		throw CUrlParsingError("invalid domain");
	}
	if (!IsValidPort(port))
	{
		throw CUrlParsingError("invalid port");
	}
	m_document = ConvertToDocument(m_document);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_protocol(protocol)
	, m_domain(domain)
	, m_document(document)
{
	if (!IsValidDomain(domain))
	{
		throw std::invalid_argument("invalid domain");
	}
	m_document = ConvertToDocument(m_document);
	m_port = defaultPortValueForProtocol.at(m_protocol);
}

std::string CHttpUrl::GetURL() const
{
	std::string url = GetProtocolString(m_protocol).append("://").append(m_domain);
	if (m_port == defaultPortValueForProtocol.at(m_protocol))
	{
		return url.append(m_document);
	}
	else
	{
		return url.append(std::to_string(m_port)).append(m_document);
	}
	return url;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

std::string CHttpUrl::GetProtocolString(Protocol protocol) const
{
	std::string result;
	for (auto [str, prot] : stringToProtocolMap)
	{
		if (protocol == prot)
			result = str;
	}
	return result;
}

