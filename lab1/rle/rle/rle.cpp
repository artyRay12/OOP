#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>
#include <iomanip>
#include <bitset>

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	Args args;

	if ((argc != 3))
	{
		cout << "Invalid number of parametres \n usage extract.txt <input File> <output File>" << endl;
		return nullopt;
	}

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}

bool Encode(ifstream& input, ofstream& output)
{
	char ch;
	string line;
		/*multimap<char, int> rleInfo;
		map<char, int> rleInfo;
		rleInfo.clear();
		map<char, int>::iterator it;

		while (input.get(ch))
		{	
			cout << setw(4) << int(ch);
			if (rleInfo.find(ch) == rleInfo.end()) {
				rleInfo.emplace(ch , 1);
			}
			else {
				rleInfo[ch]++;
			}

		}

		for (auto it = rleInfo.begin(); it != rleInfo.end(); ++it)
		{
			cout << it->first << " : " << it->second << endl;
		}*/

	string letters;
	while (getline(input, line))
	{
		for (int j = 0; j < line.size(); j++) {
			cout << bitset<8>(int(line[j])) << endl;
			int count = 1;
			
			/*while (line[j] == line[j + 1]) {
				count++;
				j++;
			}*/
			
		}
	}

	stringstream str(letters);
	while (str.get(ch))
	{

		//cout << (ch);
	}

	return true;
}

bool Rle(const string& inputFileName, const string& outputFileName)
{
	ifstream input;
	input.open(inputFileName, ios::binary);
	if (!input.is_open())
	{
		cout << "cant open input file" << endl;
		return false;
	}

	ofstream output;
	output.open(outputFileName);
	if (!output.is_open())
	{
		cout << "cant open output file" << endl;
		return false;
	}

	if (!Encode(input, output))
	{

	}

	cout << endl;
	input.close();
	input.open(inputFileName, ios::binary);
	char ch;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	if (!Rle(args->inputFileName, args->outputFileName))
	{
		cout << "SomeThingWrong";
	}
	return 0;
}
