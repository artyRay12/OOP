#include <iostream>
#include <fstream>
#include <optional>
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
	cout << argv[3] << endl;
	if ((argc != 5))
	{
		cout << "Invalid number of parametres" << endl;
		return nullopt;
	}

	if ((atoi(argv[3]) < 0) || ((atoi(argv[4]) <= 0)))
	{
		cout << "Invalid fragment start or fragment size" << endl;
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.fragmentStart = atoi(argv[3]);
	args.fragmentSize = atoi(argv[4]);
	return args;

}

void extractFragment(ifstream& input, ofstream& output, optional<Args> args)
{
	char ch;
	string fragment;
	int charNumber = 0;

	while (input.get(ch))
	{
		charNumber++;
		if ((charNumber >= args->fragmentStart) && (charNumber <= args->fragmentStart + args->fragmentSize))
		{
			if (!output.put(ch))
			{
				break;
			}
		}
	}

	if (charNumber < args->fragmentStart + args->fragmentSize)
	{
		cout << "fragment size too big" << endl;
	}
}


int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	/* Открываем входной файл */
	ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		cout << "cant open input file" << endl;
		return 1;
	}

	/* Открываем выходной файл */
	ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		cout << "cant open output file" << endl;
		return 1;
	}

	/* Копируем input -> output */
	extractFragment(input, output, args);


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
