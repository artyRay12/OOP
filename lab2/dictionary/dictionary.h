#pragma once

#include <Windows.h>
#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

const std::string EXIT = "...";
const std::string SKIP_ADD_NEW_WORD = "";

const std::string TRANSLATE_DELIMITER = " - ";
const std::string WORD_DELIMITER = ", ";

using Dictionary = std::map<std::string, std::vector<std::string>>;

void DictionaryDialog(const Dictionary& dictionary = Dictionary(), const std::string& dictionaryFileName = "");
std::vector<std::string> ParseStringToVector(const std::string &str);
void Trim(std::string& str);