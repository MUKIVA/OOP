#include <iostream>
#include <fstream>
#include "windows.h"
#include "Dictionary.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::fstream dictionaryFile("dictionary.txt", std::ios::in);
	if (!dictionaryFile.is_open())
	{
		std::cout << "Failed to open file to read\n";
		return 1;
	}
	DictionaryMap dictionary = GetDictionaryMap(dictionaryFile);
	int startDictSize = dictionary.size();
	Translate(dictionary);
	bool wasChanged = dictionary.size() != startDictSize;
	std::ofstream outDictionaryFile("dictionary.txt");
	if (!outDictionaryFile.is_open())
	{
		std::cout << "Failed to open file to save\n";
		return 1;
	}
	ExitTranslate(dictionary, outDictionaryFile, wasChanged);
	return 0;
}