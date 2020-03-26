#include "dictionary.h"
#include "fileUtilities.h"

using namespace std;

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
	}
	else
	{
		Dictionary dictionary;
		DictionaryDialog(dictionary);
	}

	return 0;
}
