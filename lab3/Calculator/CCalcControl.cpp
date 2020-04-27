#include "CCalcControl.h"
#include "boost/algorithm/string.hpp"
#include <iomanip>

using namespace std;
using namespace std::placeholders;

CCalcControl::CCalcControl(CCalculator& calculator, istream& input, ostream& output)
	: m_calc(calculator)
	, m_input(input)
	, m_output(output)
	, m_actions({ { "var", bind(&CCalcControl::CreateVar, this, _1) },
		  { "let", bind(&CCalcControl::SetVar, this, _1) },
		  { "print", bind(&CCalcControl::PrintValueByIdName, this, _1) },
		  { "fn", bind(&CCalcControl::SetFunction, this, _1) },
		  { "printvars", bind(&CCalcControl::PrintVars, this) },
		  { "printfns", bind(&CCalcControl::PrintFns, this) } })
{
}

bool CCalcControl::CalculatorDialog() const
{
	string command;
	getline(m_input, command);

	stringstream commandStream(command);
	string action;

	commandStream >> action;

	auto it = m_actions.find(action);
	if (it != m_actions.end())
	{
		return it->second(commandStream);
	}
	else
	{
		m_output << "!Error wrong command!\n";
		return false;
	}
}

bool CCalcControl::ParseStringToFunctionInfo(const string& functionBody, string& functionName, string& firstValue, string& secondValue, Operations& operand) const
{
	auto functionRhsLhs = ParseStringToRhsAndLhs(functionBody);
	if (!functionRhsLhs)
	{
		m_output << "Wrong function expression \n";
		return false;
	}

	functionName = functionRhsLhs.value().first;
	string functionExpression = functionRhsLhs.value().second;

	for (auto operation : OPERATION_ID)
	{
		size_t operationPos = functionExpression.find(operation.first);
		if (operationPos != string::npos)
		{
			operand = operation.second;
			firstValue = functionExpression.substr(0, operationPos);
			secondValue = functionExpression.substr(operationPos + 1, functionExpression.length());
			return true;
		}
	}

	firstValue = functionExpression;
	return true;
}

bool CCalcControl::SetFunction(istream& args) const
{
	string functionInString, functionName, firstValue, secondValue;
	Operations operand = Operations::none;

	args >> functionInString;

	if (!ParseStringToFunctionInfo(functionInString, functionName, firstValue, secondValue, operand))
	{
		m_output << "Invalid expression\n";
		return false;
	}

	bool isFunctionSet = m_calc.SetFunction(functionName, firstValue, secondValue, operand);
	if (!isFunctionSet)
	{
		m_output << "Invalid functon name, or expression\n";
		return false;
	}

	m_output << "function " << functionName << " created\n";

	return true;
}

bool CCalcControl::CreateVar(istream& args) const
{
	string variableName;
	args >> variableName;
	boost::trim(variableName);

	bool isVarCreated = m_calc.CreateVar(variableName);
	if (!isVarCreated)
	{
		m_output << "\"" << variableName << "\" already exist or wrong name\n";
		return false;
	}

	m_output << fixed << setprecision(2) << "\"" << variableName << "\" added\n";
	return true;
}

boost::optional<RhsAndLhs> CCalcControl::ParseStringToRhsAndLhs(const string& variable) const
{
	auto delimPosition = variable.find("=");
	if ((delimPosition == string::npos) || (delimPosition + 1 == variable.length()))
	{
		return boost::none;
	}

	string variableName = variable.substr(0, delimPosition);
	string variableValue = variable.substr(delimPosition + 1, variable.length());

	return make_pair(boost::trim_copy(variableName), boost::trim_copy(variableValue));
}

bool CCalcControl::SetVar(istream& arg) const
{
	string variable;
	arg >> variable;

	auto variableInfo = ParseStringToRhsAndLhs(boost::trim_copy(variable));
	if (!variableInfo)
	{
		m_output << "!Error can't let variable, check ur arguments\n";
		return false;
	}

	bool isVarSet = m_calc.SetVar(variableInfo.value());
	if (!isVarSet)
	{
		m_output << fixed << setprecision(2) << "Cant set \"" << variableInfo.value().first << "\" to " << variableInfo.value().second << endl;
		return false;
	}

	m_output << fixed << setprecision(2) << "Set \"" << variableInfo.value().first << "\" to " << variableInfo.value().second << endl;
	return true;
}

bool CCalcControl::PrintValueByIdName(istream& arg) const
{
	string variableName;
	arg >> variableName;

	auto variableValue = m_calc.GetValueByIdName(variableName);
	if (!variableValue)
	{
		m_output << "This var or function doestn exist\n";
		return false;
	}

	m_output << variableName << " = " << variableValue.value() << endl;
	return true;
}

bool CCalcControl::PrintVars() const
{
	for (auto& t : m_calc.GetVars())
		m_output << t.first << " = " << t.second << endl;
	return true;
}

bool CCalcControl::PrintFns() const
{
	for (auto& t : m_calc.GetFunctions())
	{
		m_output << t.first  << " : " << t.second.result << endl;
	}
	
	return true;
}