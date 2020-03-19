#pragma once
#include <iostream>
#include <cstring>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>

std::map<char, std::string> test = { {'"', "&quot"}, {'\'', "&apos"}, {'<', "&lt"}, {'>', "&gt"}, {'&', "&amp"} };
std::string HtmlEncode(std::string& str);


