#pragma once
#include <string>
#include <memory>

struct CStringListElement
{
	std::string value;
	std::shared_ptr<CStringListElement> leftLink = nullptr;
	std::shared_ptr<CStringListElement> rightLink = nullptr;
};

class CStringList
{
public:
	template <typename Iter>
	class SLIterator
	{
	public:
		using itType = Iter;
		using value_type = itType;
		using different_type = std::ptrdiff_t;
		using reference = itType&;
		using pointer = itType*;
		using iterator_category = std::random_access_iterator_tag;
		
		SLIterator(): m_ptr(nullptr){};
		SLIterator(Iter p): m_ptr(p){};
		SLIterator(const SLIterator& p): m_ptr(p){};

		SLIterator& operator=(Iter ptr)
		{
			m_ptr = ptr;
			return *this;
		}
		reference operator*() const { return *m_ptr; }
		pointer operator->() const { return m_ptr; }

		reference operator++()
		{
		
		}
		

		Iter m_ptr;
	};

	typedef SLIterator<std::shared_ptr<CStringListElement>> iterator;
	typedef SLIterator<const std::shared_ptr<CStringListElement>> const_iterator;

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	CStringList();
	~CStringList();
	bool InsertToStart(std::string str);
	bool InsertToEnd(std::string str);
	bool Clear();

	bool empty() const;
	size_t size() const;
private:
	size_t m_length;
	std::shared_ptr<CStringListElement> m_start;
	std::shared_ptr<CStringListElement> m_end;
};