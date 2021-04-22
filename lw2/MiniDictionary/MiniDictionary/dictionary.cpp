#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
#include "Dictionary.h"

using namespace std;


string ToLowerCase(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

string RemoveExtraChars(string const& str)
{
	regex SpaceReg(R"(\s+)");
	regex SideChars(R"(^[\s\{\[]+|[\s\}\]]+$)");
	return regex_replace(regex_replace(str, SideChars, ""), SpaceReg, " ");
}

optional<DictionaryItem> ParseDictionaryItem(const string& line)
{
	DictionaryItem item;
	regex keyRegex(R"(\{[A-Za-z0-9а-яА-ЯЁё ]+\})");
	regex translatedWordsRegex(R"(\[[0-9а-яА-ЯA-Za-zЁё ]+\])");
	smatch match;
	if (regex_search(line, match, keyRegex))
	{
		item.word = ToLowerCase(RemoveExtraChars(match[0]));
		auto wordsBegin = std::sregex_iterator(line.begin(), line.end(), translatedWordsRegex);
		auto wordsEnd = std::sregex_iterator();

		if (wordsBegin == wordsEnd)
		{
			return nullopt;
		}

		for (std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i)
		{
			match = *i;
			item.translatedWords.push_back(ToLowerCase(RemoveExtraChars(match[0])));
		}
	}
	else
	{
		return nullopt;
	}
	return item;
}

DictionaryMap GetDictionaryMap(std::istream& f)
{
	string line;
	DictionaryMap map;
	while (getline(f, line))
	{
		auto item = ParseDictionaryItem(line);
		if (item)
		{
			map[item->word] = item->translatedWords;
		}
	}
	return map;
}


void WriteTranslateWords(ostream& os, Words const& words)
{
	for (auto translate : words)
	{
		os << translate;
		if (translate != *(words.end() - 1))
		{
			os << ", ";
		}
	}
	cout << endl;
}

void HandleUnknownWord(DictionaryMap& d, std::string& const word)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа.\n";
	string wordInLower = ToLowerCase(word);
	string newTranslate;
	getline(cin, newTranslate);
	if (newTranslate == "")
	{
		d.erase(word);
		cout << "Слово \"" << word << "\" проигнорировано\n";
		return;
	}
	newTranslate = ToLowerCase(newTranslate);
	d[wordInLower].push_back(newTranslate);
	cout << "Слово \"" << word << "\" сохранено в словаре как \"" << newTranslate << "\".\n";
}

void HandleWord(DictionaryMap& d, std::string& const word)
{
	string wordInLower = ToLowerCase(word);
	if (!d[wordInLower].empty())
	{
		WriteTranslateWords(cout, d[wordInLower]);
	}
	else
	{
		HandleUnknownWord(d, word);
	}
}

void SaveDict(const DictionaryMap& d, ofstream& fs)
{
	fs.clear();
	//fs.seekg(0);
	for (auto [word, translateWords] : d)
	{
		fs << "{" << word << "}";
		for (string translate : translateWords)
		{
			fs << "[" << translate << "]";
		}
		fs << endl;
	}
}

void ExitTranslate(const DictionaryMap& d, ofstream& fs, bool changed)
{
	if (changed)
	{
		cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
		string userAnswer;
		getline(cin, userAnswer);
		if (userAnswer == "Y" || userAnswer == "y")
		{
			SaveDict(d, fs);
		}
		cout << "Изменения сохранены.";
	}
	cout << "До свидания.";
}

void Translate(DictionaryMap& d)
{
	string word;
	cout << "Для выхода введите \"" << EXIT_STRING << "\"\n";
	do
	{
		getline(cin, word);
		word = RemoveExtraChars(word);
		if (word.empty() || word == EXIT_STRING)
		{
			continue;
		}
		HandleWord(d, word);
	} while (word != EXIT_STRING);
}