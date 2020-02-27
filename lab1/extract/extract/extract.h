#pragma once

int checkFiles(std::ifstream& input, std::ofstream& output, bool& retflag);

bool Extract(std::ifstream& input, char& ch, int& charNumber, int start, int size, std::ofstream& output, bool& retflag);
