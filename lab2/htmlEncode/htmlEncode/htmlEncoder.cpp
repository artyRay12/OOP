#include "htmlEncoder.h"
using namespace std;

std::map<char, std::string> test = { { '"', "&quot"}, {'\'', "&apos"}, {'<', "&lt"}, {'>', "&gt"}, {'&', "&amp"} };

void Replace(string& str, size_t &strIndex)
{
	str.replace(strIndex, 1, test[str[strIndex]]);
	strIndex += test[str[strIndex]].length();
}


void HtmlEncode(string& str)
{
	char ch;
	size_t stringIndex = 0;
	stringstream stream(str);
	string encodedString;

	for (char ch : str)
	{
		if (test.find(ch) != test.end())
		{
			Replace(str, stringIndex);
		}
		stringIndex++;
	}
}

string ReadString(istream& inputStream)
{
	string line;
	getline(inputStream, line);
	return line;
}






