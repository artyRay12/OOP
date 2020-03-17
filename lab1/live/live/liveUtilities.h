#pragma once
#include <optional>
#include <vector>
#include <string>
#include <set>

const char BORDER = '*';
const char ALIVE_CELL = '#';
const char DEATH_CELL = ' ';

//std::set<char> partsOfTheMap = { BORDER, ALIVE_CELL, DEATH_CELL };

enum class CellStates {
	dead,
	alive
};

using MapLine = std::vector<char>;
using Map = std::vector<MapLine>;

using GameMapLine = std::vector<CellStates>;
using GameMap = std::vector<GameMapLine>;

struct Population
{
	size_t mapWidth = 0;
	size_t mapHeight = 0;
	GameMap map;
	GameMap nextMap;
};

void PrintGeneration(const GameMap& map, std::ostream& output);
std::optional<Map> GetMapFromFile(const std::string& inputFileName);
void GetNextGeneration(Population& map);
Population GetCurrentGeneration(const Map& map);