#pragma once
#include <Windows.h>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <optional>
#include <regex>
#include <set>
#include <sstream>
#include <string>

const std::string WORD_REPLACER = "***";

std::optional<std::set<std::string>> GetUncensoredWordsFromFile(const std::string& fileName);
std::set<std::string> GetUncensoredWords(std::istream& input);
std::string WordCensor(const std::string& word, const std::set<std::string>& uncensoredWords);
std::string StringCensor(std::istream& userInput, const std::set<std::string>& uncensoredWords);