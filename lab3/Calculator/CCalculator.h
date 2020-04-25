#pragma once
#include <map>
#include <string>
#include <iostream>
#include <cctype>
#include <boost/bind/bind.hpp>
#include <boost/optional.hpp>

enum Operations
{
	plus,
	minus,
	mult,
	divide,
	none
};

const std::map<std::string, Operations> OPERATION_ID{
	{ "+", Operations::plus },
	{ "-", Operations::minus },
	{ "*", Operations::mult },
	{ "/", Operations::divide }
};

struct FunctionData
{
	std::string name;
	std::string firstValue;
	boost::optional<std::string> secondValue = boost::none;
	boost::optional<Operations> operand = boost::none;
};


class CCalculator
{
public:
	bool CreateVar(const std::string& variableName);

	bool SetVar(const std::pair<std::string, std::string> variableInfo);
	bool SetFunction(const FunctionData& functionData);

	boost::optional<double> GetVarValue(const std::string& varName) const;
	boost::optional<double> GetFunctionValue(const std::string& varName) const;
	boost::optional<double> GetValueByName(const std::string& varName) const;

	std::map<std::string, double> GetVars() const;
	std::map<std::string, double> GetFunctions() const;

private:

	boost::optional<double> CalculateTwoOperands(double firstValue, double secondValue, Operations action);

	bool IsVariableNameCorrect(const std::string & variableName) const;
	bool IsVariableExist(const std::string& variableName) const;
	bool IsFunctionExist(const std::string& variableName) const;
	

	std::map<std::string, double> m_functions;
	std::map<std::string, double> m_variables;
};
