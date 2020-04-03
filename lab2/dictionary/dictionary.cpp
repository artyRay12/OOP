#include "dictionary.h"

using namespace std;

void Trim(string& str)
{
	str.erase(0, str.find_first_not_of(" "));
	str.erase(str.find_last_not_of(" ") + 1);
}

vector<string> ParseStringToVector(const string& str)
{
	istringstream translateStream(str);
	string word;
	vector<string> translateWords;

	while (getline(translateStream, word, ','))
	{
		Trim(word);
		translateWords.push_back(word);
	}
	return translateWords;
}

void AddWord(Dictionary& dictionary, const string& word, const string& translate)
{
	dictionary.emplace(word, ParseStringToVector(translate));
	cout << "Word \"" << word << "\" saved as \"" << translate << endl;
}

void AddNewWord(Dictionary& dictionary, const string& word)
{
	string translate;
	getline(cin, translate);

	if (!translate.empty())//(translate != SKIP_ADD_NEW_WORD)
	{
		AddWord(dictionary, word, translate);
	}
	else
	{
		cout << "Word \"" << word << "\" was ignored" << endl;
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
	if (isalpha(word[0]))
	{
		return SearchEngToRus(dictionary, word);
	}

	return SearchRusToEnd(dictionary, word);
}

void PutDictionaryInFile(ostream& output, const Dictionary& dictionary)
{
	for (auto& item : dictionary)
	{
		output << item.first << TRANSLATE_DELIMITER;

		for (auto word : item.second)
		{
			output << word << WORD_DELIMITER;
		}
		output << endl;
	}
}

void SaveNewDictionary(const Dictionary& dictionary, string dictionaryFileName)
{

	if (dictionaryFileName.empty())
	{
		dictionaryFileName = "NEWdictionary.txt";
	}

	ofstream output(dictionaryFileName, ios::app);
	PutDictionaryInFile(output, dictionary);
}

void DictionaryDialog(const Dictionary& dictionary, const string& dictionaryFileName)
{
	string word;
	Dictionary newWords;

	while (getline(cin, word))
	{
		transform(word.begin(), word.end(), word.begin(), tolower);
		Trim(word);

		if (word == EXIT)
		{
			if (!newWords.empty())
			{
				cout << "U added new words, wanna save it? Y for save\n";
				char ch;
				cin >> ch;
				if (ch == 'Y' || ch == 'y')
					SaveNewDictionary(newWords, dictionaryFileName);
			}
			break;
		}

		if (auto translate = GetTranslate(dictionary, word); translate) // чтобы работал такой if надо включить в проекте поддержку C++17
		{
			copy(translate.value().begin(), translate.value().end(), ostream_iterator<string>(cout, ","));
			cout << endl;
			continue;
		}

		if (auto translate = GetTranslate(newWords, word); translate) // чтобы работал такой if надо включить в проекте поддержку C++17
		{
			copy(translate.value().begin(), translate.value().end(), ostream_iterator<string>(cout, ","));
			cout << endl;
			continue;
		}

		cout << "Unknown word \"" << word << "\" Type translation or empty string from skip it\n";
		AddNewWord(newWords, word);
	}
}

