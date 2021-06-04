#include "CStringList.h"

CStringList::iterator CStringList::begin()
{
	return iterator(m_start);
}

CStringList::iterator CStringList::end()
{
	return iterator(m_end);
}

CStringList::const_iterator CStringList::begin() const
{
	return const_iterator(m_start);
}

CStringList::const_iterator CStringList::end() const
{
	return const_iterator(m_end);
}

CStringList::CStringList()
	: m_length(0)
	, m_start(nullptr)
	, m_end(nullptr)
{
}

CStringList::~CStringList()
{
	Clear();
}

bool CStringList::empty() const
{
	return !m_length;
}

size_t CStringList::size() const
{
	return m_length;
}

bool CStringList::InsertToStart(std::string str)
{
	std::shared_ptr<CStringListElement> tmp(new CStringListElement);
	tmp->value = str;
	tmp->rightLink = m_start;
	m_start = tmp;
	if (!m_end)
	{
		m_end = m_start;
	}
	if (tmp->rightLink)
	{
		tmp->rightLink->leftLink = tmp;
	}
	tmp = nullptr;
	++m_length;
	return true;
}

bool CStringList::InsertToEnd(std::string str)
{
	std::shared_ptr<CStringListElement> tmp(new CStringListElement);
	tmp->value = str;
	tmp->leftLink = m_end;
	m_end = tmp;
	if (!m_start)
	{
		m_start = m_end;
	}
	if (tmp->leftLink)
	{
		tmp->leftLink->rightLink = tmp;
	}
	tmp = nullptr;
	++m_length;
	return true;
}

bool CStringList::Clear()
{
	std::shared_ptr<CStringListElement> tmp(m_start);
	m_start = nullptr;
	while (tmp != m_end)
	{
		if (tmp->leftLink != nullptr)
		{
			tmp->leftLink->rightLink = nullptr;
		}
		tmp = tmp->rightLink;
	}
	tmp = nullptr;
	m_end = nullptr;
	m_length = 0;
	return false;
}
