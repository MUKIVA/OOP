#include <iostream>
#include <vector>

template <typename T>
class Comparator
{
public:
	bool operator()(T const& a, T const& b) const
	{
		return a < b;
	}
};

template <>
class Comparator<const char*>
{
public:
	bool operator()(const char* const& a, const char* const& b) const
	{
		return strcmp(a, b) < 0;
	}
};


template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.size() == 0)
	{
		return false;
	}

	T max = arr.at(0);

	for (T el : arr)
	{
		
		max = less(max, el) 
			? el 
			: max;
	}

	maxValue = max;
	return true;
}

int main()
{
	std::vector<const char*> v{"hello","world" };
	const char* d;
	FindMax(v, d, Comparator<const char*>());
	return 0;
}
