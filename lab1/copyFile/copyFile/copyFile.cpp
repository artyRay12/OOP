#include <iostream>
#include <fstream>
#include <optional>
#include "copyFile.h"
using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	/* Проверка количества аргументов */
	if (argc != 3)
	{
		cout << "Invalid number of parametres" << endl;
		return nullopt;
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;

}

void copyStreams(std::ifstream& input, std::ofstream& output)
{
	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			break;
		}
	}
}


int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		cout << "some Error \n";
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
	copyStreams(input, output);

	if (input.bad())
	{
		cout << "Failed to writing data on disk \n";
		return 1;
	}

	if (!output.flush())
	{
		cout << "Failed to writing data on disk \n";
		return 1; 
	}

    return 0;
}
