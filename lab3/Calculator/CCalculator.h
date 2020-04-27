#pragma once
#include <map>
#include <string>
#include <iostream>
#include <cctype>
#include <vector>
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

struct SFunctionData
{
	double* firstValueP;
	double* secondsValueP;
	Operations operand = Operations::none;
	void Calculate();
	double result;
};


class CCalculator
{
public:
	bool CreateVar(const std::string& variableName);

	bool SetVar(const std::pair<std::string, std::string> variableInfo);
	bool SetFunction(std::string& functionName, std::string& firstValue, std::string& secondValue, Operations& operand);

	boost::optional<double> GetValueByIdName(const std::string& varName);
	std::map<std::string, double> GetVars() const;
	std::map<std::string, SFunctionData> GetFunctions();

private:
	bool IsIdNameCorrect(const std::string & variableName) const;
	bool VariableExists(const std::string& variableName) const;
	bool FunctionExists(const std::string& variableName) const;

	double* GetPointerToValue(const std::string& varName);
	std::map<std::string, SFunctionData> m_functions;
	std::map<std::string, double> m_variables;
};

