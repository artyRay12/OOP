#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <conio.h>
#include "liveUtilities.h"

using namespace std;
set<char> chars = {'#', '*', ' '};


void PrintGeneration(const vector<vector<char>>& generation, ostream& output)
{
	for (auto& row : generation)
	{
		for (auto elem : row)
		{
			output << elem;
		}
		output << endl;
	}
}

optional<vector<char>> ParseLine(const string& line)
{
	vector<char> genLine;
	for (auto& elem : line)
	{
		if (chars.find(elem) == chars.end())
		{
			cout << "wrong char DETECTED!!!";
			return nullopt;
		}
		genLine.push_back(elem);
	}
	return genLine;
}

optional<vector<vector<char>>> GetCurrentGeneration(istream& input)
{
	vector<vector<char>> firstGeneration;
	string line;
	int lineLength = 0;

	while (getline(input, line))
	{
		auto generationLine = ParseLine(line);
		if (!generationLine)
		{
			return nullopt;
		}

		firstGeneration.push_back(generationLine.value());
		generationLine.value().clear();
	}

	return firstGeneration;
}

optional<vector<vector<char>>> GetCurrentGenerationFromFile(const string& inputFileName)
{
	ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		cout << "Can't open file: " << inputFileName << endl;
		return nullopt;
	}

	return GetCurrentGeneration(input);
}

size_t CalculateNeighbors(size_t line, size_t elem, const vector<vector<char>>& currentGeneration)
{
	size_t neighborCounter = 0;

	for (size_t i = line - 1; i <= line + 1; i++)
	{
		for (size_t j = elem - 1; j <= elem + 1; j++)
		{		
			if ((currentGeneration[i][j] == '#') && !((i == line) && (j == elem)))
			{
				neighborCounter++;
			}
		}
	}

	return neighborCounter;
}


vector<vector<char>> GetNextGeneration(const vector<vector<char>>& currentGeneration)
{
	vector<vector<char>> nextGeneration;
	vector<char> nextGenerationLine;
	size_t neighborCounter = 0;

	for (size_t i = 0; i < currentGeneration.size(); i++)
	{
		for (size_t j = 0; j < currentGeneration[i].size(); j++)
		{
			if (currentGeneration[i][j] != '*')
			{
				neighborCounter = CalculateNeighbors(i, j, currentGeneration);

				if ((neighborCounter == 2) || (neighborCounter == 3))
				{
					nextGenerationLine.push_back('#');
				}
				else
				{
					nextGenerationLine.push_back(' ');
				}
			}
			else
			{
				nextGenerationLine.push_back('*');
			}
		}

		nextGeneration.push_back(nextGenerationLine);
		nextGenerationLine.clear();
		neighborCounter = 0;
	}
	return nextGeneration;
}
