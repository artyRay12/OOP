#include <iostream>
#include <fstream>
#include <optional>
#include <string>

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
	if ((argc != 5))
	{
		cout << "Invalid number of parametres" << endl;
		return nullopt;
	}

	if ((stoi(argv[3]) < 0) || ((stoi(argv[4]) < 0)))
	{
		cout << "Invalid fragment start or fragment size" << endl;
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.fragmentStart = stoi(argv[3]);
	args.fragmentSize = stoi(argv[4]);
	return args;

}

bool ExtractFragment(ifstream& input, ofstream& output, int start, int size)
{
	char ch;
	int charNumber = 0;

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
		cout << "fragment size too big" << endl;
		return false;
	}
	else 
	{
		return true;
	}
}

bool CheckFiles(ifstream& input, ofstream& output, string inputFileName, string outputFileName)
{
	input.open(inputFileName);
	if (!input.is_open())
	{
		cout << "cant open input file" << endl;
		return false;
	}

	output.open(outputFileName);
	if (!output.is_open())
	{
		cout << "cant open output file" << endl;
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

	ifstream input;
	ofstream output;
	if (!CheckFiles(input, output, args->inputFileName, args->outputFileName))
	{
		return 1;
	}

	/* extract fragment */
	if (!ExtractFragment(input, output, args->fragmentStart, args->fragmentSize))
	{
		cout << "fail with extract" << endl;
		return 1;
	}

	if (input.bad())
	{
		cout << "Failed to reading data from disk \n";
		return 1;
	}

	if (!output.flush())
	{
		cout << "Failed to writing data on disk \n";
		return 1;
	}

	return 0;
}
