#include "htmlEncoder.h"
using namespace std;

vector<std::pair<char, std::string>> HtmlEntities = { { '"', "&quot" }, { '\'', "&apos" }, { '<', "&lt" }, { '>', "&gt" }, { '&', "&amp" } };

optional<string> GetHtmlEntityByChar(char ch)
{
	for (auto pair : HtmlEntities)
	{
		if (pair.first == ch)
		{
			return pair.second;
		}
	}

	return nullopt;
}

string HtmlEncode(const string& str)
{
	string encodedString;

	for (auto ch : str)
	{
		auto htmlEntity = GetHtmlEntityByChar(ch);
		if (htmlEntity)
		{
			encodedString += htmlEntity.value();
			continue;
		}
		 
		encodedString += ch;
	}

	return encodedString;
}

string ReadString(istream& inputStream)
{
	string line;
	getline(inputStream, line);
	return line;
}
