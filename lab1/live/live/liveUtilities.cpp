#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <iterator>
#include "liveUtilities.h"
#include <set>

using namespace std;
set<char> partsOfTheMap = { ALIVE_CELL, DEATH_CELL };

const size_t MIN_HEIGHT = 3;
const size_t MAX_HEIGHT = 256;

const size_t MIN_WIDTH = 3;
const size_t MAX_WIDTH = 256;

void SetCellAlive(CellStates& cell)  // void SetCellAlive(GameMap & map, size_t mapRowIndex, size_t mapColIndex)
{
	cell = CellStates::alive;
}

void SetCellDeath(CellStates& cell)
{
	cell = CellStates::dead;
}

bool IsCellAlive(CellStates cell)
{
	return cell == CellStates::alive;
}

void SetCellState(CellStates& cellState, CellStates cellState1)
{
	cellState = cellState1;
}

size_t GetGenHeight(const Generation& gen)
{
	return gen.size();
}

size_t GetGenWidth(const Generation& gen)
{
	return gen[0].size();
}


void PrintGeneration(const Generation& gen, ostream& output)
{
	for (size_t i = 0; i <= GetGenWidth(gen) + 1; i++) output << BORDER;
	cout << endl;

	for (auto& row : gen)
	{
		output << BORDER;
		for (CellStates elem : row)
		{
			if (elem == CellStates::alive) output << ALIVE_CELL;
			if (elem == CellStates::dead) output << DEATH_CELL;
		}
		output << BORDER;
		output << endl;
	}

	for (size_t i = 0; i <= GetGenWidth(gen) + 1; i++) output << BORDER;
	cout << endl;
}



optional<Map> GetMap(istream& input)
{
	Map map;
	string line;
	
	while (getline(input, line))
	{
		if (line.empty())
		{
			cout << "Error!\nRemove empty lines from ur map please\n";
			return nullopt;
		}

		MapLine mapLine(line.begin(), line.end());
		map.push_back(mapLine);
	}

	return map;
}

bool IsMapSizeValid(size_t width, size_t height)
{
	return (width <= MAX_WIDTH) && (height <= MAX_HEIGHT);
}

bool IsValidMap(const Map& map)
{
	size_t mapWidth = map[0].size();
	size_t mapHeight = map.size();

	size_t firstLineIndex = 0;
	size_t lastLineIndex = map.size() - 1;

	size_t firstColIndex = 0;
	size_t lastColIndex = map[0].size() - 1;

	if (!IsMapSizeValid(mapWidth, mapHeight))
	{
		cout << "Map too big\n";
		return false;
	}

	for (size_t lineIndex = 0; lineIndex < mapHeight; lineIndex++)
	{
		if (mapWidth != map[lineIndex].size())
		{
			cout << "Ur lines have diff size";
			return false;
		}

		for (size_t colIndex = 0; colIndex < mapWidth; colIndex++)
		{
			if (((lineIndex == firstLineIndex) || (lineIndex == lastLineIndex)) || ((colIndex == firstColIndex) || (colIndex == lastColIndex)))
			{
				if (map[lineIndex][colIndex] != BORDER)
				{
					cout << "Check ur borders! They have wrong symbol\nUse only '*' as border!";
					return false;
				}
			}
			else if (partsOfTheMap.find(map[lineIndex][colIndex]) == partsOfTheMap.end())
			{
				cout << "Check generation elements!\nUse -- '*' as dead cell\n    -- '#' as alive";
				return false;
			}
		}
	}
	return true;
}

optional<Map> GetMapFromFile(const string& inputFileName)
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

	auto map = GetMap(input);
	if (!map)
	{
		cout << "GetMap Error!";
		return nullopt;
	}

	if (!IsValidMap(map.value()))
	{
		cout << "IsValid Error";
		return nullopt;
	}

	return map;
}

Population GetCurrentGeneration(const Map& map)
{
	Population generation;

	generation.genWidth = map[0].size();
	generation.genHeight = map.size();

	generation.current.resize(generation.genHeight);


	for (size_t lineIndex = 0; lineIndex < generation.genHeight; lineIndex++)
	{
		generation.current[lineIndex].resize(generation.genWidth);
		for (size_t colIndex = 0; colIndex < generation.genWidth; colIndex++)
		{
			if (map[lineIndex][colIndex] == BORDER)
			{
				continue;
			}

			if (map[lineIndex][colIndex] == ALIVE_CELL)
			{
				SetCellAlive(generation.current[lineIndex][colIndex]);
			}

			if (map[lineIndex][colIndex] == DEATH_CELL)
			{
				SetCellDeath(generation.current[lineIndex][colIndex]);
			}
		}
	}
	return generation;
}


size_t CalculateNeighbors(size_t line, size_t elem, const Generation& currentGeneration, size_t mapWidth, size_t mapHeight)
{
	size_t neighborCounter = 0; 

	for (size_t lineIndex = line - 1; lineIndex <= line + 1; lineIndex++)
	{
		for (size_t colIndex = elem - 1; colIndex <= elem + 1; colIndex++)
		{		
			if ((lineIndex >= 0) && (lineIndex < mapHeight) && (colIndex >= 0) && (colIndex < mapWidth))
			{
				if ((IsCellAlive(currentGeneration[lineIndex][colIndex])) && !((lineIndex == line) && (colIndex == elem)))
				{
					neighborCounter++;
				}
			}
		}
	}

	return neighborCounter;
}


void GetNextGeneration(Population &generation)
{
	size_t neighborCounter = 0;
	generation.next = generation.current;

	for (size_t lineIndex = 0; lineIndex < GetGenHeight(generation.current); lineIndex++)
	{
		for (size_t colIndex = 0; colIndex < GetGenWidth(generation.current); colIndex++)
		{
			neighborCounter = CalculateNeighbors(lineIndex, colIndex, generation.current, GetGenWidth(generation.current), GetGenHeight(generation.current));

			if (IsCellAlive(generation.current[lineIndex][colIndex]))
			{
				if ((neighborCounter > 3) || (neighborCounter < 2))
				{
					SetCellDeath(generation.next[lineIndex][colIndex]);
				}
			}

			if (!IsCellAlive(generation.current[lineIndex][colIndex]))
			{
				if (neighborCounter == 3)
				{
					SetCellAlive(generation.next[lineIndex][colIndex]);
				}
			}
		}
		neighborCounter = 0;
	}
}
