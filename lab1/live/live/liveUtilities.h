#pragma once
#include <optional>
#include <vector>
#include <string>
#include <set>


std::optional<std::vector<std::vector<char>>> live(const std::string& inputFileName);
void PrintGeneration(const std::vector<std::vector<char>>& generation, std::ostream& output);
std::vector<std::vector<char>> GetNextGeneration(const std::vector<std::vector<char>>& currentGeneration);
std::optional<std::vector<std::vector<char>>> GetCurrentGenerationFromFile(const std::string& inputFileName);