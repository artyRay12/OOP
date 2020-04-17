#pragma once
#include "CCalculator.h"
#include <functional>
#include <iostream>
#include <map>
#include <sstream>

class CCalcControl
{
public:
	CCalcControl(CCalculator calculator, std::istream& input);
	bool CalculatorDialog();

private:
	bool SetVar(std::istream& variableName);

	CCalculator m_calc;
	std::istream& m_input;

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actions;
};
