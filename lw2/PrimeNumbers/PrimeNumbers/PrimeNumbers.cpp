#include "GeneratePrimeNumbersSet.h"
#include "windows.h"
#include <iostream>
#include <set>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int upperBound = 0;
	while (std::cin >> upperBound)
	{
		std::set<int> primeNums = GeneratePrimeNumbersSet(upperBound);
		if (!primeNums.size())
		{
			std::cout << "Set is empty\n";
		}
		WritePrimeSet(std::cout, primeNums);
	}
	return 0;
}
