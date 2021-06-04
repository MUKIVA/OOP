#include "CMyArray.h"


template <typename T>
CMyArray<T>::CMyArray(const CMyArray<T> &arr)
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

template<typename T>
inline void CMyArray<T>::Append(const T &value)
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

template <typename T>
T & CMyArray<T>::GetBack()
{
    assert(GetSize() != 0);
    return m_end[-1];
}

template <typename T>
const T & CMyArray<T>::GetBack() const
{
    assert(GetSize() != 0);
    return m_end[-1];
}

template<typename T>
size_t CMyArray<T>::GetSize() const
{
    return m_end - m_begin;
}

template <typename T>
size_t CMyArray<T>::GetCapacity() const
{
    return m_endOfCapacity - m_begin;
}
