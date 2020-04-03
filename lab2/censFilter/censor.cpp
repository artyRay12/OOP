#include "censor.h"

using namespace std;

string ToLower(const string& str)
{
	string lowerString;
	for (char ch : str)
	{
		lowerString += tolower(ch);
	}

	return lowerString;
}

set<string> GetUncensoredWords(istream& input)
{
	string word;
	set<string> uncensoredWords;
	while (getline(input, word))
	{
		uncensoredWords.insert(word);
	}

	return uncensoredWords;
}

optional<set<string>> GetUncensoredWordsFromFile(const string& fileName)
{
	ifstream input(fileName);
	if (!input.is_open())
	{
		return nullopt;
	}

	return GetUncensoredWords(input);
}

string Word�ensor(const string& word, const set<string>& uncensoredWords)
{
	if (uncensoredWords.find(ToLower(word)) != uncensoredWords.end())
	{
		return WORD_REPLACER;
	}

	return word;
}

string String�ensor(istream& userInput, const set<string>& uncensoredWords)
{
	string str;
	string censoredStr;
	getline(userInput, str);

	string word;

	for (char ch : str)
	{
		if (isalpha(ch))
		{
			word += ch;
		}
		else
		{
			censoredStr += Word�ensor(word, uncensoredWords);
			censoredStr += ch;
			word.clear();
		}
	}

	if (!word.empty()) //��������� ���������� ����� ���� ��� ����
	{
		censoredStr += Word�ensor(word, uncensoredWords);
	}

	return censoredStr;
}