#include "Decode.h"
#include <iostream>
#include <iterator>
#include <map>
#include <regex>

std::regex GetHtmlRegexToDecode(DecodeMap const& m)
{
	std::string regexString;
	for (auto& html : m)
	{
		regexString += "(" + html.first + ")" + "|";
	}
	if (!regexString.empty())
	{
		regexString.pop_back();
	}
	std::regex htmlRegex(regexString);
	return htmlRegex;
}
std::string HtmlDecode(std::string const& html)
{
	static std::map<std::string, std::string> decode = { { "&quot;", "\"" },
		{ "&apos;", "'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" } };
	std::string result;
	std::regex htmlRegex = GetHtmlRegexToDecode(decode);
	auto wordsBegin = std::sregex_iterator(html.begin(), html.end(), htmlRegex);
	auto wordsEnd = std::sregex_iterator();

	if (wordsBegin == wordsEnd)
	{
		return html;
	}

	std::smatch lastmatch;
	for (std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i)
	{
		std::smatch match = *i;
		result += (std::string)match.prefix() + decode[match[0]];
		lastmatch = match;
	}
	result += lastmatch.suffix();
	return result;
}
