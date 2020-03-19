#pragma once
#include <optional>
#include <vector>
#include <string>
#include <set>

const char BORDER = '*';
const char ALIVE_CELL = '#';
const char DEATH_CELL = ' ';

using MapLine = std::vector<char>;
using Map = std::vector<MapLine>;


enum class CellStates {
	dead,
	alive
};

using GenerationLine = std::vector<CellStates>;
using Generation = std::vector<GenerationLine>;

struct Population
{
	size_t genWidth = 0;
	size_t genHeight = 0;
	Generation current;
	Generation next;
};

void PrintGeneration(const Generation& map, std::ostream& output);
std::optional<Map> GetMapFromFile(const std::string& inputFileName);
void GetNextGeneration(Population& map);
Population GetCurrentGeneration(const Map& map);