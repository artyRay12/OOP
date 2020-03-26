#include "fileUtilities.h"
using namespace std;

pair<string, vector<string>> ParseLine(const string& str)
{
	string word;
	string wordTranslation;
	pair<string, vector<string>> dictionaryElem;

	auto wordEnd = str.find(TRANSLATE_DELIMITER);
	dictionaryElem.first = str.substr(0, wordEnd);

	auto translateStart = wordEnd + TRANSLATE_DELIMITER.length();
	wordTranslation = str.substr(translateStart);
	dictionaryElem.second = ParseStringToVector(wordTranslation);

	return dictionaryElem;
}

Dictionary GetDictionary(istream& input)
{
	Dictionary dictionary;
	string str;
	pair<string, vector<string>> dictionaryElem;

	while (getline(input, str))
	{
		dictionaryElem = ParseLine(str);
		dictionary.emplace(dictionaryElem.first, dictionaryElem.second);
	}

	return dictionary;
}

optional<Dictionary> GetDictionaryFromFile(const string& dictionaryFileName)
{
	ifstream input(dictionaryFileName);
	if (!input.is_open())
	{
		return nullopt;
	}

	if (input.peek() == EOF)
	{
		return nullopt;
	}

	return GetDictionary(input);
}