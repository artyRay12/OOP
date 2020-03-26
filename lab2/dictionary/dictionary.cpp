#include "dictionary.h"

using namespace std;

string Trim(const string& str)
{
	string trimmedStr = str;
	string chars = " ";
	trimmedStr.erase(0, trimmedStr.find_first_not_of(chars));
	trimmedStr.erase(trimmedStr.find_last_not_of(chars) + 1);

	return trimmedStr;
}

vector<string> ParseStringToVector(const string& str)
{
	istringstream translateStream(str);
	string word;
	vector<string> translateWords;

	while (getline(translateStream, word, ','))
	{
		translateWords.push_back(Trim(word));
	}

	return translateWords;
}

void AddWord(Dictionary& dictionary, const string& word, const string& translate)
{
	dictionary.emplace(word, ParseStringToVector(translate));
	cout << "New word was added\n";
}

void AddNewWord(Dictionary& dictionary, const string& word)
{
	string translate;
	getline(cin, translate);
	if (translate != SKIP_ADD_NEW_WORD)
	{
		AddWord(dictionary, word, translate);
	}
}

optional<vector<string>> SearchEngToRus(const Dictionary& dictionary, const string& word)
{
	if (auto it = dictionary.find(word); it != dictionary.end())
	{
		return it->second;
	}

	return nullopt;
}

optional<vector<string>> SearchRusToEnd(const Dictionary& dictionary, const string& word)
{
	for (auto item : dictionary)
	{
		for (auto translation : item.second)
		{
			if (translation == word)
			{
				vector<string> translationWords;
				translationWords.push_back(item.first);
				return translationWords;
				
			}
		}
	}

	return nullopt;
}

optional<vector<string>> GetTranslate(const Dictionary& dictionary, const string& word)
{
	if (isalpha(Trim(word)[0]))
	{
		return SearchEngToRus(dictionary, word);
	}

	return SearchRusToEnd(dictionary, word);
}

/*
void PutDictionaryInFile(ostream& output, const Dictionary& dictionary)
{
	for (auto& item : dictionary)
	{
		output << endl
			   << item.first << " " << item.second;
	}
}

void SaveNewDictionary(const Dictionary& dictionary, string dictionaryFileName)
{

	if (dictionaryFileName.empty())
	{
		dictionaryFileName = "dictionary.txt";
	}

	ofstream output(dictionaryFileName, ios::app);
	PutDictionaryInFile(output, dictionary);
}
*/

void DictionaryDialog(const Dictionary& dictionary, const string& dictionaryFileName)
{
	string word;
	Dictionary newWords;

	while (getline(cin, word))
	{
		/*if (word == EXIT)
		{
			if (!newWords.empty())
			{
				cout << "U added new words, wanna save it? Y/N";
				char ch;
				cin >> ch;
				if (ch == 'Y' || ch == 'y')
					SaveNewDictionary(newWords, dictionaryFileName);
			}

			break;
		}*/

		if (auto translate = GetTranslate(dictionary, word); translate) // чтобы работал такой if надо включить в проекте поддержку C++17
		{
			copy(translate.value().begin(), translate.value().end(), ostream_iterator<string>(cout, " "));
			cout << endl;
			continue;
		}

		if (auto translate = GetTranslate(newWords, word); translate) // чтобы работал такой if надо включить в проекте поддержку C++17
		{
			copy(translate.value().begin(), translate.value().end(), ostream_iterator<string>(cout, " "));
			cout << endl;
			continue;
		}

		cout << "Cant find \"" << word << "\" in dictionary.\nType translation if u want add new word, or empty string for skip it\n";
		AddNewWord(newWords, word);
	}
}