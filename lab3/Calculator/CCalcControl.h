#pragma once
#include "CCalculator.h"
#include <functional>
#include <iostream>
#include <map>
#include <sstream>

typedef std::pair<std::string, std::string> VariableInfo;

class CCalcControl
{
public:
	CCalcControl(CCalculator calculator, std::istream& input);
	bool CalculatorDialog();

private:
	bool CreateVar(std::istream& variableName);
	bool SetVar(std::istream& variableName);
	bool SetFunction(std::istream& variableName);
	bool PrintVariableValue(std::istream& arg);
	bool PrintVars();
	boost::optional<VariableInfo> ParseStringByEqualSign(const std::string& variable);
	boost::optional<FunctionData> ParseStringToFunction(const std::string& functionBody);
	

	CCalculator m_calc;
	std::istream& m_input;

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actions;
};
