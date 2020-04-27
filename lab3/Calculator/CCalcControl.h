#pragma once
#include "CCalculator.h"
#include <functional>
#include <iostream>
#include <map>
#include <sstream>

typedef std::pair<std::string, std::string> RhsAndLhs;

class CCalcControl
{
public:
	CCalcControl(CCalculator& calculator, std::istream& input, std::ostream& output);
	bool CalculatorDialog() const;

private:
	bool CreateVar(std::istream& variableName) const;
	bool SetVar(std::istream& variableName) const;
	bool SetFunction(std::istream& variableName) const;
	bool PrintValueByIdName(std::istream& arg) const;
	bool PrintVars() const;
	bool PrintFns() const;

	boost::optional<RhsAndLhs> ParseStringToRhsAndLhs(const std::string& variable) const;
	bool ParseStringToFunctionInfo(const std::string& functionBody, std::string& functionName, std::string& firstValue, std::string& secondValue, Operations& operand) const;
	
	CCalculator &m_calc;
	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actions;
};
