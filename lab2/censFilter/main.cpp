#include "censor.h"
using namespace std;

optional<string> GetUncensoredWordsFileName(int argc, char* argv[])
{
	if (argc == 2)
	{
		return argv[1];
	}

	return nullopt;
}

int main(int argc, char* argv[])
{
	auto uncensoredWordsFileName = GetUncensoredWordsFileName(argc, argv);
	if (!uncensoredWordsFileName)
	{
		return 1;
	}

	auto uncensoredWords = GetUncensoredWordsFromFile(uncensoredWordsFileName.value());
	string censoredStr = String—ensor(cin, uncensoredWords.value());

	cout << censoredStr << endl;
}
