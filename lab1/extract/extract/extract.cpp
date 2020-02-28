#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "extract.h"

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
	int fragmentStart;
	int fragmentSize;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	Args args;

	if ((argc != 5))
	{
		cout << "Invalid number of parametres \n usage extract.txt <input File> <output File> <fragment start> <fragment length>" << endl;
		return nullopt;
	}

	try
	{
		args.fragmentStart = stoi(argv[3]);
		args.fragmentSize = stoi(argv[4]);
	}

	catch (const exception & err)
	{
		cout << err.what();
		return nullopt;
	}

	if ((args.fragmentStart < 0) || ((args.fragmentSize < 0)))
	{
		cout << "Invalid fragment start or fragment size" << endl;
		return nullopt;
	}

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;

}

bool Extract(ifstream& input, ofstream& output, int &start, int &size)
{
	int charNumber = 0;
	char ch;
	while (input.get(ch))
	{
		charNumber++;
		if ((charNumber >= start) && (charNumber <= start + size) && (size != 0))
		{
			if (!output.put(ch))
			{
				break;
			}
		}
	}
	cout << charNumber << endl;
	if (charNumber < start + size)
	{
		cout << "fragment size too big" << endl;
		return false;
	}

	return true;
}

bool ExtractFragment(const string& inputFileName, const string& outputFileName, int start, int size)
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

	if (!Extract(input, output, start, size))
	{
		return false;
	}

	if (input.bad())
	{
		cout << "Failed to reading data from disk \n";
		return false;
	}

	if (!output.flush())
	{
		cout << "Failed to writing data on disk \n";
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	if (!ExtractFragment(args->inputFileName, args->outputFileName, args->fragmentStart, args->fragmentSize))
	{
		cout << "fail with extract" << endl;
		return 1;
	}

	return 0;
}

