#pragma once
#include <string>
#include <cassert>
#include <map>

//Стандартный порт выводиться не должен +
// Сделать тест на https://google.com:!23 +
// Нужно смотреть переполнение порта +
// Приводить протокол к нижнему регистру +
// Исправить регистр символов в названиях методов +
// Методы класса, которые не используют поля класса, сделять статическими либо сделать свободными функциями +


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