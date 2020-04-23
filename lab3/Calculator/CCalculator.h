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
	CCalculator() = default;
	~CCalculator() = default;
	bool CreateVar(const std::string& variableName);
	bool SetVar(const std::pair<std::string, std::string> variableInfo);
	bool SetFunction(const FunctionData& functionData);
	boost::optional<double> GetVarValue(const std::string& varName);
	boost::optional<double> GetFunctionValue(const std::string& varName);
	boost::optional<double> GetValueByName(const std::string& varName);
	std::map<std::string, double> GetVars() const;
	
private:
	bool IsVariableNameCorrect(const std::string & variableName) const;
	bool IsVariableExist(const std::string& variableName) const;
	bool IsFunctionExist(const std::string& variableName) const;
	

	std::map<std::string, double> m_variables;
	std::map<std::string, double> m_functions;
};
