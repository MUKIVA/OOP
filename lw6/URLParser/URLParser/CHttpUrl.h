#pragma once
#include <string>
#include <cassert>
#include <map>

enum class Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDocument() const;
	std::string GetDomain() const;
	unsigned short GetPort() const;
	Protocol GetProtocol() const;
	std::string GetProtocolString(Protocol protocol) const;


private:
	const std::map<Protocol, unsigned short> m_defaultPortValueForProtocol{
		{ Protocol::HTTP, 80 },
		{ Protocol::HTTPS, 443 }
	};

	bool isValidProtocol(std::string const& protocol) const;
	bool isValidDomain(std::string const& domain) const;
	bool isValidPort(const unsigned short port) const;
	std::string ConvertToDocument(std::string& document) const;
	unsigned short ConvertToPort(std::string& port) const;
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
};