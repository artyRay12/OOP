#pragma once
#include <map>
#include <string>
#include <iostream>

class CCalculator
{
public:
	CCalculator() = default;
	~CCalculator() = default;
	bool SetVar(const std::string& variableName);

private:
	std::map<std::string, double> m_variables;
};
