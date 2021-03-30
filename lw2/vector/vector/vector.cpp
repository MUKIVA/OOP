#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include "MultiplyByMinimum.h"

int main()
{
	FloatVector vector;
	float num;
	std::cout << "Please enter a sequence of real numbers(press \"q\" to exit):\n";
	while (std::cin >> num)
	{
		vector.push_back(num);
	}
	MultiplyByMinimum(vector);
	VectorIterator it;
	for (it = vector.begin(); it < vector.end(); it++)
	{
		std::cout << std::fixed << std::setprecision(3) << *it << ' ';
	}
	std::cout << std::endl;
	return 0;
}