#pragma once

#include <algorithm>
#include <new>

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
        reference& operator->() const{ return *m_item; }
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

        friend MyType operator+(difference_type offset, const MyType& it)
        {
            return it + offset;
        }
    public:
        IteratorBase(T* item)
            : m_item(item)
        {
        }

    protected:
        T* m_item = nullptr;

    };

public:
    CMyArray() = default;
    CMyArray(const CMyArray& arr);
    void Append(const T& value);
    T& GetBack();
    const T& GetBack() const;
    size_t GetSize() const;
    size_t GetCapacity() const;
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

private:
	static void DeleteItems(T* begin, T* end)
	{
		DestroyItems(begin, end);
		RawDealloc(begin);
	}
    static void CopyItems(const T* srcBegin, T* srcEnd, const T*  newBegin, T*& newEnd)
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
