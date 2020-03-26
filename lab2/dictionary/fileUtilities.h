#pragma once
#include <Windows.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "dictionary.h"

std::optional<Dictionary> GetDictionaryFromFile(const std::string& dictionaryFileName);
Dictionary GetDictionary(std::istream& input);