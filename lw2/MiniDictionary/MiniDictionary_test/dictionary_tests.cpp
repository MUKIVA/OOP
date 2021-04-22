#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <utility>
#include <locale>

#include "../../../Catch/catch.hpp"

#include "../MiniDictionary/Dictionary.h"

using namespace std;

SCENARIO("RemoveExtraChars: The string may contain extra spaces around the edges")
{
	string str = "    dog    ";
	REQUIRE(RemoveExtraChars(str) == "dog");
}

SCENARIO("RemoveExtraChars: The string may contain extra spaces at the edges and special characters '[', ']', '{', '}'")
{
	std::string str = "[{    dog    }]";
	REQUIRE(RemoveExtraChars(str) == "dog");
}

SCENARIO("RemoveExtraChars: A string can contain multiple words")
{
	std::string str = "The    Red     Square";
	REQUIRE(RemoveExtraChars(str) == "The Red Square");
}

SCENARIO("RemoveExtraChars: The string may be empty ")
{
	std::string str = "";
	REQUIRE(RemoveExtraChars(str) == "");
}

SCENARIO("RemoveExtraChars: The string can be filled with spaces")
{
	std::string str = "       ";
	REQUIRE(RemoveExtraChars(str) == "");
}

SCENARIO("ParseDictionaryItem: A string can contain a key, but no values")
{
	string str = "{cat}";
	auto result = ParseDictionaryItem(str);
	REQUIRE(result == nullopt);
}

SCENARIO("ParseDictionaryItem: A string can be empty")
{
	string str = "";
	auto result = ParseDictionaryItem(str);
	REQUIRE(result == nullopt);
}

SCENARIO("ParseDictionaryItem: A string can contain a key and value")
{
	string str = "{cat}[кот]";
	auto readRes = ParseDictionaryItem(str);
 	DictionaryItem item;
	item.word = "cat";
	item.translatedWords = { "кот" };
	REQUIRE(readRes);
	DictionaryItem res = std::move(*readRes);
	REQUIRE((res.word == item.word && res.translatedWords == item.translatedWords));
}

SCENARIO("ParseDictionaryItem: A string can contain a key and values")
{
	string str = "{cat}[кот][кошка]";
	auto readRes = ParseDictionaryItem(str);
	DictionaryItem item;
	item.word = "cat";
	item.translatedWords = { "кот", "кошка" };
	REQUIRE(readRes);
	DictionaryItem res = std::move(*readRes);
	REQUIRE((res.word == item.word && res.translatedWords == item.translatedWords));
}

SCENARIO("ParseDictionaryItem: A string can contain a key in upper case")
{
	setlocale(LC_ALL, "");
	string str = "{CaT}[КоТ][коШка]";
	auto readRes = ParseDictionaryItem(str);
	DictionaryItem item;
	item.word = "cat";
	item.translatedWords = { "кот", "кошка" };
	REQUIRE(readRes);
	DictionaryItem res = std::move(*readRes);
	REQUIRE((res.word == item.word && res.translatedWords == item.translatedWords));
}

SCENARIO("GetDictionaryMap: Get dict map from file ")
{
	setlocale(LC_ALL, "");
	fstream dictionaryFile("dictMap.txt", ios::in | ios::out);
	DictionaryMap map = GetDictionaryMap(dictionaryFile);
	DictionaryMap expectedMap{ 
		{ "cat", {"кот", "кошка"} },
		{ "dog", {"собака"} },
		{ "meat", {"мясо"} }
	};
	REQUIRE(map == expectedMap);
}

SCENARIO("GetDictionaryMap: Get dict map from file with line skip ")
{
	setlocale(LC_ALL, "");
	fstream dictionaryFile("dictMapWLS.txt", ios::in | ios::out);
	DictionaryMap map = GetDictionaryMap(dictionaryFile);
	DictionaryMap expectedMap{
		{ "cat", { "кот", "кошка" } },
		{ "dog", { "собака" } },
		{ "meat", { "мясо" } }
	};
	REQUIRE(map == expectedMap);
}

SCENARIO("GetDictionaryMap: Get dict map from empty file")
{
	setlocale(LC_ALL, "");
	fstream dictionaryFile("emptyDict.txt", ios::in | ios::out);
	DictionaryMap map = GetDictionaryMap(dictionaryFile);
	DictionaryMap expectedMap{};
	REQUIRE(map == expectedMap);
}

SCENARIO("ToLowerCase: empty str")
{
	setlocale(LC_ALL, "");
	std::string str = "";
	str = ToLowerCase(str);
	std::string expectedStr = "";
	REQUIRE(str == expectedStr);
}

SCENARIO("ToLowerCase: str in lower")
{
	setlocale(LC_ALL, "");
	std::string str = "test";
	str = ToLowerCase(str);
	std::string expectedStr = "test";
	REQUIRE(str == expectedStr);
}

SCENARIO("ToLowerCase: str in upper case")
{
	setlocale(LC_ALL, "");
	std::string str = "TEST";
	str = ToLowerCase(str);
	std::string expectedStr = "test";
	REQUIRE(str == expectedStr);
}

SCENARIO("ToLowerCase: str in upper case with rus chars")
{
	setlocale(LC_ALL, "");
	std::string str = "ТЕСТ";
	str = ToLowerCase(str);
	std::string expectedStr = "тест";
	REQUIRE(str == expectedStr);
}

SCENARIO("WriteTranslateWords: array may be empty")
{
	setlocale(LC_ALL, "");
	vector<string> words{};
	WriteTranslateWords(cout, words);
}

SCENARIO("WriteTranslateWords: array may be filled")
{
	setlocale(LC_ALL, "");
	vector<string> words{"кот", "кошка"};
	WriteTranslateWords(cout, words);
}