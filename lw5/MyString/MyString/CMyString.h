#pragma once
#include <string>
#include <iterator>
#include <cassert>


class CMyString
{
public:

	static const size_t READ_BUFFER_SIZE = 50;

	template <typename Iter>
	class SIterator
	{
		friend class SIterator<const Iter>;
	public:
		using itType = SIterator<Iter>;
		using value_type = Iter;
		using different_type = std::ptrdiff_t;
		using reference = value_type&;
		using pointer = value_type*;
		using iterator_category = std::random_access_iterator_tag;

		SIterator() = default;
		SIterator(const SIterator& it)
			: m_ptr(it.m_ptr)
		{
		}
		SIterator(Iter* ptr)
			: m_ptr(ptr){};

		itType& operator=(Iter* ptr)
		{
			m_ptr = ptr;
			return *this;
		}
		itType& operator+=(const different_type offset)
		{
			m_ptr += offset;
			return *this;
		}
		itType& operator-=(const different_type offset)
		{
			m_ptr -= offset;
			return *this;
		}
		reference& operator*() const { return *m_ptr; }
		pointer operator->() const { return m_ptr; }
		reference& operator[](const size_t index) 
		{
			return m_ptr[index];
		}

		itType& operator++()
		{
			m_ptr = m_ptr + 1;
			return *this;
		}
		itType operator++(int)
		{
			auto prev = *this;
			++(*this);
			return prev;
		}
		itType& operator--()
		{
			m_ptr = m_ptr - 1;
			return *this;
		}
		itType operator--(int)
		{
			auto prev = *this;
			--(*this);
			return prev;
		}
		itType operator-(size_t num) const { return SIterator(m_ptr - num); }
		different_type operator-(const SIterator& it) const { return m_ptr - it.m_ptr; }
		itType operator+(const different_type offset) const
		{
			itType self(m_ptr);
			return self += offset; 
		}

		friend itType operator+(const different_type offset, const itType& it)
		{
			return it + offset;
		}

		friend bool operator==(SIterator const& left, SIterator const& right) { return left.m_ptr == right.m_ptr; }
		friend bool operator!=(SIterator const& left, SIterator const& right) { return left.m_ptr != right.m_ptr; }
		friend bool operator>(SIterator const& left, SIterator const& right) { return left.m_ptr > right.m_ptr; }
		friend bool operator<(SIterator const& left, SIterator const& right) { return left.m_ptr < right.m_ptr; }
		friend bool operator>=(SIterator const& left, SIterator const& right) { return left.m_ptr >= right.m_ptr; }
		friend bool operator<=(SIterator const& left, SIterator const& right) { return left.m_ptr <= right.m_ptr; }

	protected:
		value_type* m_ptr = nullptr;
	};
	

	typedef SIterator<char> iterator;
	typedef SIterator<const char> const_iterator;

	friend class iterator;
	friend class const_iterator;

	iterator begin();
	iterator end();

	std::reverse_iterator<iterator> rbegin();
	std::reverse_iterator<iterator> rend();

	std::reverse_iterator<const_iterator> rbegin() const;
	std::reverse_iterator<const_iterator> rend() const;


	const_iterator begin() const;
	const_iterator end() const;


	friend bool operator==(CMyString const& left, CMyString const& right);
	friend bool operator!=(CMyString const& left, CMyString const& right);
	friend bool operator>(CMyString const& left, CMyString const& right);
	friend bool operator<=(CMyString const& left, CMyString const& right);
	friend bool operator<(CMyString const& left, CMyString const& right);
	friend bool operator>=(CMyString const& left, CMyString const& right);
	friend CMyString operator+(CMyString const& left, CMyString const& right);
	friend std::ostream& operator<<(std::ostream& os, CMyString const& str);
	friend std::istream& operator>>(std::istream& is, CMyString& str);


	CMyString& operator=(CMyString const& other);
	CMyString& operator+=(CMyString const& right);
	char& operator[](size_t index);

	CMyString();
	CMyString(const char * pString);
	CMyString(std::string const& stlString);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(const char* pString, size_t length);
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	~CMyString();

	void Clear();
	size_t GetLength() const;

private:
	char* m_str;
	size_t m_length;
};
