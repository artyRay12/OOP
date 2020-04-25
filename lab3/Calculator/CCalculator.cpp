#include "CCalculator.h"
#include <functional>
using namespace std;

boost::optional<double> CCalculator::CalculateTwoOperands(double firstValue, double secondValue, Operations action)
{
	double result = numeric_limits<double>::quiet_NaN();
	switch (action)
	{
	case Operations::plus:
		result = firstValue + secondValue;
		break;
	case Operations::minus:
		result = firstValue - secondValue;
		break;
	case Operations::mult:
		result = firstValue * secondValue;
		break;
	case Operations::divide:
		if (secondValue == 0)
		{
			
			return boost::none;
		}
		return result = firstValue / secondValue;
		break;
	default:
		break;
	}

	return result;
}

bool CCalculator::IsVariableExist(const string& variableName) const
{
	auto it = m_variables.find(variableName);
	if (it != m_variables.end())
	{
		return true;
	}

	return false;
}

bool CCalculator::IsFunctionExist(const string& variableName) const
{
	auto it = m_functions.find(variableName);
	if (it != m_functions.end())
	{
		return true;
	}

	return false;
}

bool CCalculator::IsVariableNameCorrect(const string& variableName) const
{
	if (variableName.empty())
	{
		return false;
	}

	if (isdigit(variableName[0]))
	{
		return false;
	}

	return find_if(variableName.begin(), variableName.end(),
			   [](char ch) { return !(isalnum(ch) || (ch == '_')); })
		== variableName.end();
}

bool CCalculator::CreateVar(const string& variableName)
{
	if ((!IsVariableNameCorrect(variableName)) || (IsVariableExist(variableName)))
	{
		
		return false;
	}

	m_variables.emplace(variableName, numeric_limits<double>::quiet_NaN());
	return true;
}

bool CCalculator::SetVar(pair<string, string> variableInfo)
{
	string variableName = variableInfo.first;
	if (!IsVariableNameCorrect(variableName))
	{
		return false;
	}

	string variableValue = variableInfo.second;
	try
	{
		size_t pos = 0;
		stof(variableValue, &pos);
		if (pos != variableValue.length())
		{
			return false;
		}

		m_variables[variableInfo.first] = stof(variableValue);
		return true;
	}
	catch (exception e)
	{
		if (!IsVariableExist(variableValue))
		{
			return false;
		}

		m_variables[variableName] = m_variables[variableValue];
	}

	return true;
}

boost::optional<double> CCalculator::GetVarValue(const string& varName) const
{
	auto it = m_variables.find(varName);
	if (it != m_variables.end())
	{
		return it->second;
	}

	return boost::none;
}

boost::optional<double> CCalculator::GetFunctionValue(const string& varName) const
{
	auto it = m_functions.find(varName);
	if (it != m_functions.end())
	{
		return it->second;
	}

	return boost::none;
}

boost::optional<double> CCalculator::GetValueByName(const string& varName) const
{
	auto value = GetVarValue(varName);
	if (value)
	{
		return value.value();
	}

	value = GetFunctionValue(varName);
	if (value)
	{
		return value.value();
	}

	return boost::none;
}

map<string, double> CCalculator::GetVars() const
{
	return m_variables;
}

map<string, double> CCalculator::GetFunctions() const
{
	return m_functions;
}

bool CCalculator::SetFunction(const FunctionData& functionData)
{
	if (!IsVariableNameCorrect(functionData.name))
	{
		return false;
	}

	if (IsFunctionExist(functionData.name))
	{
		return false;
	}

	if (!functionData.operand)
	{
		if (IsVariableExist(functionData.firstValue))
		{
			m_functions.emplace(functionData.name, m_variables[functionData.firstValue]);
			return true;
		}

		if (IsFunctionExist(functionData.firstValue))
		{
			m_functions.emplace(functionData.name, m_functions[functionData.firstValue]);
			return true;
		}

		return false;
	}

	auto firstValue = GetValueByName(functionData.firstValue);
	if (!firstValue)
	{
		return false;
	}

	auto secondValue = GetValueByName(functionData.secondValue.value());
	if (!secondValue)
	{
		return false;
	}

	auto result = CalculateTwoOperands(firstValue.value(), secondValue.value(), functionData.operand.value());
	if (!result)
	{
		
		return false;
	}

	m_functions.emplace(functionData.name, result.value());
	return true;
}