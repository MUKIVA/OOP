#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <regex>
#include <map>
#include <algorithm>


const unsigned short PROTOCOL_INDEX = 1;
const unsigned short HOST_INDEX = 3;
const unsigned short PORT_INDEX = 5;
const unsigned short START_DOCUMENT_INDEX = 6;
const unsigned short DOCUMENT_INDEX = 7;

const std::map<std::string, Protocol> stringToProtocolMap{
	{ "http", Protocol::HTTP },
	{ "https", Protocol::HTTPS }
};

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::regex urlReg("(.+)"
					  "(://)"
					  "([^/^:]+)"
					  "(:)?"
					  "(\\d+)?"
					  "(/)?"
					  "(.*)?");
	std::smatch urlMatch;
	if (regex_match(url, urlMatch, urlReg))
	{
		std::string protocol = urlMatch[PROTOCOL_INDEX].str();
		std::string domain = urlMatch[HOST_INDEX].str();
		std::string port = urlMatch[PORT_INDEX].matched ? urlMatch[PORT_INDEX].str() : "";
		std::string document = urlMatch[DOCUMENT_INDEX].str();

		if (!isValidProtocol(protocol))
		{
			throw CUrlParsingError("invalid protocol");
		}

		if (!isValidDomain(domain))
		{
			throw CUrlParsingError("invalid domain");
		}

		m_protocol = stringToProtocolMap.at(protocol);
		m_domain = domain;
		m_port = !port.empty()
			? ConvertToPort(port)
			: m_defaultPortValueForProtocol.at(m_protocol);
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
	if (!isValidDomain(domain))
	{
		throw CUrlParsingError("invalid domain");
	}
	if (!isValidPort(port))
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
	if (!isValidDomain(domain))
	{
		throw std::invalid_argument("invalid domain");
	}
	m_document = ConvertToDocument(m_document);
	m_port = m_defaultPortValueForProtocol.at(m_protocol);
}

std::string CHttpUrl::GetURL() const
{
	
	return GetProtocolString(m_protocol).append("://").append(m_domain).append(":").append(std::to_string(m_port)).append(m_document);
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

bool CHttpUrl::isValidProtocol(std::string const& protocol) const
{
	return (stringToProtocolMap.find(protocol) != stringToProtocolMap.end());
}

bool CHttpUrl::isValidDomain(std::string const& domain) const
{
	return !(domain.empty());
}

bool CHttpUrl::isValidPort(const unsigned short port) const
{
	return port > 0;
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

std::string CHttpUrl::ConvertToDocument(std::string& document) const
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

unsigned short CHttpUrl::ConvertToPort(std::string& port) const
{
	unsigned short result = stoi(port);
	if (!isValidPort(result))
		throw CUrlParsingError("invalid port");
	return result;
}
