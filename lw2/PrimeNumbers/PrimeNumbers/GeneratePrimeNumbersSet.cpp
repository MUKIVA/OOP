#include "GeneratePrimeNumbersSet.h"
#include <iostream>
#include <vector>

typedef std::set<int> PrimeSet;
typedef std::vector<bool> Mask;
const int MAX_UPPER_BOUND = 100000000;

Mask GetPrimeNumMask(int upperBound)
{
	const int MASK_SIZE = upperBound + 1;
	Mask mask(MASK_SIZE, true);
	mask[0] = false;
	for (int i = 2; i * i <= upperBound; i++)
	{
		for (int k = i + i; k <= upperBound; k += i)
		{
			mask[k] = false;
		}
	}
	return mask;
}

bool WritePrimeSet(std::ostream& os, std::set<int>& set)
{
	for (int num : set)
	{
		os << num << '\t';
	}
	os << std::endl;
	return true;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	PrimeSet set;
	if (upperBound < 0 || upperBound > MAX_UPPER_BOUND)
	{
		return set;
	}
	Mask mask = GetPrimeNumMask(upperBound);
	for (int i = 2; i <= upperBound; i++)
	{
		if (mask[i])
		{
			set.insert(set.end(), i);
		}
	}
	return set;
}
