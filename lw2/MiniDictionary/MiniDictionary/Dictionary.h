#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <optional>

using DictionaryMap = std::map<std::string, std::vector<std::string>>;
using Words = std::vector<std::string>;
const std::string EXIT_STRING = "...";

struct DictionaryItem
{
	std::string word;
	Words translatedWords;
};

std::string RemoveExtraChars(std::string const& str);
std::optional<DictionaryItem> ParseDictionaryItem(const std::string& line);
DictionaryMap GetDictionaryMap(std::istream& f);
std::string ToLowerCase(std::string str);
void WriteTranslateWords(std::ostream& os, Words const& words);
void HandleUnknownWord(DictionaryMap& d, std::string& const word);
void HandleWord(DictionaryMap& d, std::string& const word);
void SaveDict(const DictionaryMap& d, std::ofstream& fs);
void ExitTranslate(const DictionaryMap& d, std::ofstream& fs, bool changed);
void Translate(DictionaryMap& d);



