#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <set>
#include "liveUtilities.h"

using namespace std;

struct Args
{
	string inputFileName;
	optional<string> outputFileName = nullopt;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	Args args;

	if ((argc != 3) && (argc != 2))
	{
		cout << "Invalid number of parametres \nUsage live.exe <input File> <output File>" << endl;
		return nullopt;
	}

	args.inputFileName = argv[1];
	if (argc == 3)
	{
		args.outputFileName = argv[2];
	}

	return args;
}

optional<ofstream> GetOutputStream(const string& outputFileName)
{
	ofstream output(outputFileName);
	if (!output.is_open())
	{
		return nullopt;
	}

	return output;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	auto currentGeneration = GetCurrentGenerationFromFile(args->inputFileName);
	if (!currentGeneration)
	{
		return 1;
	}

	if (!args->outputFileName)
	{
		PrintGeneration(GetNextGeneration(currentGeneration.value()), cout);
	}
	else
	{
		auto output = GetOutputStream(args->outputFileName.value());
		if (!output)
		{
			return 1;
		}

		PrintGeneration(GetNextGeneration(currentGeneration.value()), output.value());
	}

	return 0;
}
