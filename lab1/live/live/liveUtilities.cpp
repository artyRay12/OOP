#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <iostream>
#include <conio.h>
#include "liveUtilities.h"
#include <set>

const char BORDER = '*';
const char ALIVE_CELL = '#';
const char DEATH_CELL = ' ';

enum CellStates {
	dead,
	alive
};

struct Population
{
	size_t mapWidth = 0;
	size_t mapHeight = 0;
	vector<vector<CellStates>> population;
};

using namespace std;

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

bool isValidMap(const vector<vector<char>>& generation)
{

	if ((generation.size() > 256) || (generation.size() < 3))
	{
		cout << "Error!\nWrong size of ur map, please use 3x3..256x256 sizes\n";
		return false;
	}

	size_t lineLength = generation[0].size();

	for (size_t i = 0; i < generation.size(); i++)
	{
		if ((generation[i].size() > 256) || (generation[i].size() < 3))
		{
			cout << "Error!\nWrong size of ur map, please use 3x3..256x256 sizes\n";
			return false;
		}

		for (size_t j = 0; j < generation[i].size(); j++)
		{

			if (lineLength != generation[i].size())
			{
				cout << "Error!\n Ur lines Your line should have same length\n";
				return false;
			}

			if (((i == 0) || (i == generation.size() - 1)) && (generation[i][j] != '*'))
			{
				cout << "Error!\nCheck ur borders!\n";
				return false;
			}

			if (((j == 0) || (j == generation[i].size() - 1)) && (generation[i][j] != '*'))
			{
				cout << "Error!\nCheck ur borders!\n";
				return false;
			}

			if ((i != 0 && i != generation.size() - 1) && (j != 0 && j != generation[i].size() - 1))
			{
				if ((generation[i][j] != ' ') && (generation[i][j] != '#'))
				{
					cout << "Error!\nWrong symbol on map!\n" << "line = " << i << "\nelem = " << j;
					return false;
				}
			}
		}
	}

	return true;
}
optional<CellStates> ParseLine(const string& line)
{
	CellStates cellState;
	for (auto& state: line)
	{
		if ((state != ALIVE_CELL) || (state != DEATH_CELL) || (state != BORDER))
		{
			cout << "Wrong symbol" << endl;
			return nullopt;
		}
	}

	return 
}

optional<Population> GetCurrentGeneration(istream& input)
{
	Population generation;
	string line;
	unsigned int lineCounter = 0;
	char ch;

	while (input.get(ch))
	{
		auto cellState = getCellState(line);
		if (!generationLine)
		{
			return nullopt;
		}

		generation.push_back(generationLine.value());
		generationLine.value().clear();
		lineCounter++;
	}

	if (!isValidMap(generation))
	{
		return nullopt;
	}

	return generation;
}

optional<Population> GetCurrentGenerationFromFile(const string& inputFileName)
{
	ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		cout << "Can't open file: " << inputFileName << endl;
		return nullopt;
	}

	if (input.peek() == EOF)
	{
		cout << "Your file is empty!\n";
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
