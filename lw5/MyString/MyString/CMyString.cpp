#include "CMyString.h"
#include <iostream>


std::ostream& operator<<(std::ostream& os, CMyString const& str)
{
	const char* data = str.GetStringData();
	for (size_t i = 0; i < str.m_length; i++)
	{
		os << data[i];
	}
	return os;
}

std::istream& operator>>(std::istream& is, CMyString& str)
{
	char* buffer = new char[CMyString::READ_BUFFER_SIZE + 1];
	char ch;
	bool stringIsFinded = false;
	size_t index = 0;
	size_t bufferSizeMultiplier = 1;
	while (is.get(ch))
	{
		if (ch == ' ' && !stringIsFinded)
		{
			continue;
		}
		if (ch == ' ' && stringIsFinded)
		{
			break;
		}
		stringIsFinded = true;
		buffer[index] = ch;
		index++;
		if (index >= CMyString::READ_BUFFER_SIZE * bufferSizeMultiplier)
		{
			++bufferSizeMultiplier;
			char* newBuffer = new char[CMyString::READ_BUFFER_SIZE * bufferSizeMultiplier];
			memcpy(newBuffer, buffer, index);
			delete[] buffer;
			buffer = newBuffer;
			newBuffer = nullptr;
		}
	}
	buffer[index] = '\0';
	if (stringIsFinded)
	{
		delete[] str.m_str;
		str.m_str = buffer;
		str.m_length = index;
	}
	buffer = nullptr;
	return is;
}

CMyString::iterator CMyString::begin()
{
	return iterator(m_str);
}

CMyString::iterator CMyString::end()
{
	return iterator(m_str + m_length);
}

std::reverse_iterator<CMyString::iterator> CMyString::rbegin()
{
	return std::reverse_iterator<iterator>(end());
}

std::reverse_iterator<CMyString::iterator> CMyString::rend()
{
	return std::reverse_iterator<iterator>(begin());
}

std::reverse_iterator<CMyString::const_iterator> CMyString::rbegin() const
{
	return std::reverse_iterator<const_iterator>(end());
}

std::reverse_iterator<CMyString::const_iterator> CMyString::rend() const
{
	return std::reverse_iterator<const_iterator>(begin());
}

CMyString::const_iterator CMyString::begin() const
{
	return const_iterator(m_str);
}

CMyString::const_iterator CMyString::end() const
{
	return const_iterator(m_str + m_length);
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (m_str == other.m_str)
	{
		return *this;
	}
	char* tmp = new char[other.m_length + 1];
	memcpy(tmp, other.m_str, other.m_length + 1);
	this->Clear();
	m_length = other.m_length;
	m_str = tmp;
	tmp = nullptr;
	return *this;
}

CMyString& CMyString::operator+=(CMyString const& right)
{
	*this = *this + right;
	return *this;
}

char& CMyString::operator[](size_t index)
{
	if (index > m_length)
	{
		throw std::out_of_range("index out of range");
	}
	return this->m_str[index];
}

CMyString::CMyString()
	: m_str(new char[1])
	, m_length(0)
{
	m_str[0] = '\0';
}

CMyString::CMyString(const char* pString)
	: m_length(std::strlen(pString))
{
	m_str = new char[m_length + 1]; 
	memcpy(m_str, pString, m_length + 1);
}

CMyString::CMyString(std::string const& stlString)
	: m_length(stlString.size())
{
	m_str = new char[m_length + 1];
	memcpy(m_str, stlString.c_str(), m_length + 1);
}

CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
{
	m_str = new char[m_length + 1];
	memcpy(m_str, pString, m_length + 1);
	m_str[m_length] = '\0';
}

const char* CMyString::GetStringData() const
{
	return m_str;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		return CMyString();
	}
	if (start + length > m_length)
	{
		length = m_length - start;
	}
	char* substring = new char[length + 1];
	for (size_t i = start, j = length; j != 0; j--, i++)
	{
		substring[i] = m_str[i];
	}
	substring[length] = '\0';
	return substring;
}

CMyString::CMyString(CMyString const& other)
	: m_length(other.m_length)
{
	m_str = new char[m_length + 1];
	memcpy(m_str, other.m_str, m_length + 1);
}

CMyString::CMyString(CMyString&& other) noexcept
{
	this->m_length = other.m_length;
	this->m_str = other.m_str;
	other.m_str = nullptr;
	other.m_length = 0;
}

CMyString::~CMyString()
{
	if (m_str != nullptr)
	{
		delete[] m_str;
	}
}

void CMyString::Clear()
{
	if (m_str != nullptr)
	{
		char* tmp = new char[1];
		tmp[0] = '\0';
		delete[] m_str;
		m_str = tmp;
		m_length = 0;
		tmp = nullptr;
	}
}

size_t CMyString::GetLength() const
{
	return m_length;
}

bool operator==(CMyString const& left, CMyString const& right)
{
	if (left.m_length != right.m_length)
	{
		return false;
	}
	const char* leftData = left.GetStringData();
	const char* rightData = right.GetStringData();
	for (size_t i = 0; i < left.m_length; i++)
	{
		if (leftData[i] != rightData[i])
		{
			return false;
		}
	}
	return true;
}

bool operator!=(CMyString const& left, CMyString const& right)
{
	return !(left == right);
}

bool operator>(CMyString const& left, CMyString const& right)
{
	if (left.m_length == right.m_length)
	{
		for (size_t i = 0; i < left.m_length; i++)
		{
			if (left.m_str[i] != right.m_str[i])
			{
				return left.m_str[i] > right.m_str[i];
			}
		}
	}
	return left.m_length > right.m_length;
}

bool operator<=(CMyString const& left, CMyString const& right)
{
	return !(left > right);
}

bool operator<(CMyString const& left, CMyString const& right)
{
	if (left.m_length == right.m_length)
	{
		for (size_t i = 0; i < left.m_length; i++)
		{
			if (left.m_str[i] != right.m_str[i])
			{
				return left.m_str[i] < right.m_str[i];
			}
		}
	}
	return left.m_length < right.m_length;
}

bool operator>=(CMyString const& left, CMyString const& right)
{
	return !(left < right);
}

CMyString operator+(CMyString const& left, CMyString const& right)
{
	size_t totalLength = left.m_length + right.m_length;
	char* totalString = new char[totalLength + 1];
	memcpy(totalString, left.m_str, left.m_length);
	memcpy(totalString + left.m_length, right.m_str, right.m_length + 1);
	return totalString;
}
