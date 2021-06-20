#pragma once

#include <algorithm>
#include <new>
#include <stdexcept>
#include <iterator>

template <typename T>
class CMyArray
{
    template <bool IsConst>
    class IteratorBase
    {
        friend class IteratorBase<true>;
    public:
        using MyType = IteratorBase<IsConst>;
        using value_type = std::conditional_t<IsConst, const T, T>;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        IteratorBase() = default;
        IteratorBase(const IteratorBase<false>& other)
            :m_item(other)
        {
        }

        reference& operator*() const{ return *m_item; }
        pointer operator->() const{ return m_item; }
        MyType& operator+=(difference_type offset)
        {
            m_item += offset;
            return *this;
        }

        MyType operator+(difference_type offset) const
        {
            MyType  self(m_item);
            return self += offset;
        }
		MyType& operator++()
		{
			m_item = m_item + 1;
			return *this;
		}
		MyType operator++(int)
		{
			auto prev = *this;
			++(*this);
			return prev;
		}
		MyType& operator--()
		{
			m_item = m_item - 1;
			return *this;
		}
		MyType operator--(int)
		{
			auto prev = *this;
			++(*this);
			return prev;
		}

        friend MyType operator+(difference_type offset, const MyType& it)
        {
            return it + offset;
        }
		friend bool operator!=(MyType const& left, MyType const& right)
		{
			return left.m_item != right.m_item;
		}
	public:
        IteratorBase(T* item)
            : m_item(item)
        {
        }

    public:
        T* m_item = nullptr;

    };

public:
    CMyArray() = default;
	CMyArray(CMyArray const& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}
	CMyArray(CMyArray&& other) noexcept
	{
		std::swap(this->m_begin, other.m_begin);
		std::swap(this->m_end, other.m_end);
		std::swap(this->m_endOfCapacity, other.m_endOfCapacity);
	}

    void Append(const T& value)
	{
		if (m_end == m_endOfCapacity)
		{
			size_t newCapacity = std::max(size_t(1), GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T* newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				new (newEnd) T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else
		{
			new (m_end) T(value);
			++m_end;
		}
	}
	void Resize(size_t newSize)
	{
		auto oldBegin = m_begin;
		auto oldEnd = m_end;
		if (newSize != 0)
		{
			auto newBegin = RawAlloc(newSize);
			auto newEnd = newBegin;
			try
			{
				for (newEnd = newBegin; newSize != 0; ++oldBegin, ++newEnd, --newSize)
				{
					if (oldBegin < oldEnd)
						new (newEnd) T(*oldBegin);
					else
						new (newEnd) T();
				}
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = newEnd;
		}
	}
	void Clear()
	{
		DestroyItems(m_begin, m_end);
		m_end = m_begin;
		m_endOfCapacity = m_end;
	}

    T& GetBack()
	{
		if (GetSize() == 0)
		{
			throw std::out_of_range("Called with empty array");
		}
		return m_end[-1];
	}
    const T& GetBack() const
	{
		assert(GetSize() != 0);
		return m_end[-1];
	}
    size_t GetSize() const
	{
		return m_end - m_begin;
	}
    size_t GetCapacity() const
	{
		return m_endOfCapacity - m_begin;
	}
	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
    }

    using iterator = IteratorBase<false>;
    using const_iterator = IteratorBase<true>;

    iterator begin()
    {
        return m_begin;
    }
    iterator end()
    {
        return m_end;
    }

    const_iterator begin() const
    {
        return m_begin;
    }
    const_iterator end() const
    {
        return m_end;
    }

	std::reverse_iterator<iterator> rbegin()
	{
		return std::reverse_iterator<iterator>(end());
	}
	std::reverse_iterator<iterator> rend()
	{
		return std::reverse_iterator<iterator>(begin());
	}

	std::reverse_iterator<const_iterator> rbegin() const
	{
		return std::reverse_iterator<iterator>(end());
	}
	std::reverse_iterator<const_iterator> rend() const
	{
		return std::reverse_iterator<iterator>(begin());
	}


	CMyArray<T> operator=(CMyArray<T> const& right)
	{
		Clear();
		const auto size = right.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(right.m_begin, right.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
		return *this;
	}
	CMyArray operator=(CMyArray&& right) noexcept
	{
		std::swap(m_begin, right.m_begin);
		std::swap(m_end, right.m_end);
		std::swap(m_endOfCapacity, right.m_endOfCapacity);
		return *this;
	}

	T& operator[](size_t n)
	{
		if (n < 0 || n >= GetSize())
		{
			throw std::out_of_range("out of range");
		}

		return *(m_begin + n);
	}

private:
	static void DeleteItems(T* begin, T* end)
	{
		DestroyItems(begin, end);
		RawDealloc(begin);
	}
    static void CopyItems(const T* srcBegin, T* srcEnd,  T*  newBegin, T*& newEnd)
	{
		for (newEnd = newBegin; srcBegin != srcEnd; ++srcBegin, ++newEnd)
		{
			new (newEnd) T(*srcBegin);
		}
	}
	static void DestroyItems(T* from, T* to)
	{
		{
			while (to != from)
			{
				--to;
				to->~T();
			}
		}
	}
    static  T* RawAlloc(size_t n)
	{
	    size_t memSize = n * sizeof (T);
		T* p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
		    throw std::bad_alloc();
		}
		return p;
	}
	static void RawDealloc(T* p)
	{
		free(p);
	}


private:
    T* m_begin = nullptr;
    T* m_end = nullptr;
    T* m_endOfCapacity = nullptr;
};
