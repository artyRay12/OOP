#include "dictionary.h"
#include <Windows.h>
#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

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

optional<string> GetDictionaryFileName(int argc, char* argv[])
{
	if (argc == 2)
	{
		return argv[1];
	}
	
	return nullopt;
	
}

void SetLang()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

int main(int argc, char* argv[])
{
	SetLang();

	auto dictionaryFileName = GetDictionaryFileName(argc, argv);
	if (dictionaryFileName)
	{
		auto dictionary = GetDictionaryFromFile(dictionaryFileName.value());
		if (!dictionary)
		{
			cout << "Can't read ur file";
			return 1;
		}

		DictionaryDialog(dictionary.value(), dictionaryFileName.value());
		return 0;
	}

	Dictionary dictionary;
	DictionaryDialog(dictionary);

	return 0;
}
