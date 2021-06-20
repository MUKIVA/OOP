#pragma once
#include <string>
#include <cassert>
#include <map>

//����������� ���� ���������� �� ������ +
// ������� ���� �� https://google.com:!23 +
// ����� �������� ������������ ����� +
// ��������� �������� � ������� �������� +
// ��������� ������� �������� � ��������� ������� +
// ������ ������, ������� �� ���������� ���� ������, ������� ������������ ���� ������� ���������� ��������� +


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
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
};