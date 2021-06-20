#include <iostream>
#include <string>
#include <vector>
#include <iterator>

struct Sportsman
{
	std::string name;
	size_t heigh = 0;
	size_t weight = 0;
};

template <typename T, typename Less>
bool FindMaxEx(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	auto first = arr.begin();
	auto last = arr.end();
	auto max = arr.begin();

	while (first != last)
	{
		max = less(*max, *first)
			? first 
			: max;
		
		++first;
	}

	maxValue = *max;
	return true;
}

void PrintSportInfo(std::ostream& os, Sportsman const& sportsmen)
{
	os << "Name: " << sportsmen.name << std::endl;
	os << "Heigh: " << sportsmen.heigh << std::endl;
	os << "Weight: " << sportsmen.weight << std::endl;
	os << std::endl;
}

int main()
{
	std::vector<Sportsman> sportsmansInfo;
	sportsmansInfo.push_back({ "Ivan", 172, 70 });
	sportsmansInfo.push_back({ "Marat", 178, 64 });
	sportsmansInfo.push_back({ "Egor", 170, 75 });
	Sportsman maxWeight;
	Sportsman maxHeight;
	FindMaxEx(sportsmansInfo, maxHeight, [](Sportsman const& a, Sportsman const& b) {
		return a.heigh < b.heigh;
	});
	FindMaxEx(sportsmansInfo, maxWeight, [](Sportsman const& a, Sportsman const& b) {
		return a.weight < b.weight;
	});
	PrintSportInfo(std::cout, maxWeight);
	PrintSportInfo(std::cout, maxHeight);
	return 0;
}
