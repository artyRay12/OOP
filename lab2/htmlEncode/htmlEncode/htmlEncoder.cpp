#include "htmlEncoder.h"
using namespace std;

std::map<char, std::string> test = { { '"', "&quot"}, {'\'', "&apos"}, {'<', "&lt"}, {'>', "&gt"}, {'&', "&amp"} };

void Replace(string& str, size_t &strIndex)
{
	str.replace(strIndex, 1, test[str[strIndex]]);
}

void HtmlEncode(string& str)
{
	char ch;
	size_t stringIndex = 0;
	stringstream stream(str);
	string encodedString;

	while(str[stringIndex] != '\0')
	{
		if (test.find(str[stringIndex]) != test.end())
		{
			Replace(str, stringIndex);
			stringIndex += test[str[stringIndex]].length() - 1;
		}
		else
		{
			stringIndex++;
		}
	}
}

string ReadString(istream& inputStream)
{
	string line;
	getline(inputStream, line);
	return line;
}






