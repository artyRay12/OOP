#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>

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
	map<char, int> rleInfo;
	rleInfo.clear();
	map<char, int>::iterator it;

	while (input.get(ch))
	{	
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
	}

	return 1;
}

bool Rle(const string& inputFileName, const string& outputFileName)
{
	ifstream input;
	input.open(inputFileName);
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
    
}
