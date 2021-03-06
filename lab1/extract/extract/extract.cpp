﻿#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "extract.h"

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
	int fragmentStart = 0;
	int fragmentSize = 0;
};


optional<Args> ParseArgs(int argc, char* argv[])
{
	Args args;
	size_t fragmentStartPos = 0;
	size_t fragmentSizePos = 0;

	if ((argc != 5))
	{
		return nullopt;
	}

	string fragmentStartNumberLength = argv[3];
	string fragmentSizeNumberLength = argv[4];

	try
	{
		args.fragmentStart = stoi(argv[3], &fragmentStartPos);
		args.fragmentSize = stoi(argv[4], &fragmentSizePos);
	}
	catch (const exception & err)
	{
		cout << err.what();
		return nullopt;
	}

	if ((fragmentStartPos != fragmentStartNumberLength.length()) || (fragmentSizePos != fragmentSizeNumberLength.length()))
	{
		cout << "Error!\nPlease check <fragment start> or <fragment length>\n";
		return nullopt;
	}

	if ((args.fragmentStart < 0) || ((args.fragmentSize < 0)))
	{
		cout << "Invalid <fragment start> or <fragment length>" << endl;
		return nullopt;
	}

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;

}

bool Extract(istream& input, ostream& output, int start, int size)
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

	if (charNumber < start + size)
	{
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
		cout << "fragment size too big" << endl;
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
		cout << "Invalid number of parametres \n usage extract.txt <input File> <output File> <fragment start> <fragment length>" << endl;
		return 1;
	}


	if (!ExtractFragment(args->inputFileName, args->outputFileName, args->fragmentStart, args->fragmentSize))
	{
		cout << "fail with extract" << endl;
		return 1;
	}

	return 0;
}

