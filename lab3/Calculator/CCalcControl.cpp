#include "CCalcControl.h"
#include "boost/algorithm/string.hpp"

using namespace std;
using namespace std::placeholders;

CCalcControl::CCalcControl(CCalculator calculator, istream& input)
	: m_calc(calculator)
	, m_input(input)
	, m_actions({
		  { "var", bind(&CCalcControl::CreateVar, this, _1) },
		  { "let", bind(&CCalcControl::SetVar, this, _1) },
		  { "print", bind(&CCalcControl::PrintVariableValue, this, _1) },
		  { "fn", bind(&CCalcControl::SetFunction, this, _1) },
		  { "printvars", bind(&CCalcControl::PrintVars, this) }
		  //{ "printfns", bind(&CCalcControl::PrintFunctions, this) }
	  })
{
}

bool CCalcControl::CalculatorDialog()
{
	string command;
	getline(m_input, command);

	stringstream commandStream(command);
	string action;

	commandStream >> action;

	auto it = m_actions.find(action);
	if (it != m_actions.end())
	{
		it->second(commandStream);
	}
	else
	{
		cout << "!Error wrong command!\n";
	}

	return true;
}

boost::optional<FunctionData> CCalcControl::ParseStringToFunction(const string& functionBody)
{
	auto functionData = ParseStringByEqualSign(functionBody);
	if (!functionData)
	{
		return boost::none;
	}

	FunctionData function;
	function.name = functionData.value().first;
	string functionExpression = functionData.value().second;

	for (auto id : OPERATION_ID)
	{
		size_t operationPos = functionExpression.find(id.first);
		if (operationPos != string::npos)
		{
			function.operand = id.second;
			function.firstValue = functionExpression.substr(0, operationPos);
			function.secondValue = functionExpression.substr(operationPos + 1, functionExpression.length());
			return function;
		}
	}

	function.firstValue = functionExpression;
	return function;
}

bool CCalcControl::SetFunction(istream& args)
{
	string functionBody;
	args >> functionBody;

	auto function = ParseStringToFunction(functionBody);
	if (!function)
	{
		return false;
	}

	m_calc.SetFunction(function.value());

	return true;
}

bool CCalcControl::CreateVar(istream& args)
{
	string variableName;
	args >> variableName;
	boost::trim(variableName);

	bool isVarCreated = m_calc.CreateVar(variableName);
	if (!isVarCreated)
	{
		cout << "\"" << variableName << "\" already exist or wrong name\n";
		return false;
	}

	cout << "\"" << variableName << "\" added\n";
	return true;
}

boost::optional<VariableInfo> CCalcControl::ParseStringByEqualSign(const string& variable)
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

bool CCalcControl::SetVar(istream& arg)
{
	string variable;
	arg >> variable;

	auto variableInfo = ParseStringByEqualSign(boost::trim_copy(variable));
	if (!variableInfo)
	{
		cout << "!Error can't let variable, check ur arguments\n";
		return false;
	}

	bool isVarSet = m_calc.SetVar(variableInfo.value());
	return true;
}

bool CCalcControl::PrintVariableValue(istream& arg)
{
	string variableName;
	arg >> variableName;

	auto variableValue = m_calc.GetValueByName(variableName);
	if (!variableValue)
	{
		cout << "This var or function doestn exist\n";
		return false;
	}

	cout << variableName << " = " << variableValue.value() << endl;
	return true;
}

bool CCalcControl::PrintVars()
{
	for (auto& t : m_calc.GetVars())
		cout << t.first << " = " << t.second << endl;
	return true;
}
