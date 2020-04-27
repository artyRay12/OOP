#include "CCalculator.h"
#include <functional>
using namespace std;

void SFunctionData::Calculate()
{
	if (operand == Operations::none)
	{
		result = *firstValuePtr;
		return;
	}

	if ((*firstValuePtr == numeric_limits<double>::quiet_NaN())
		|| (*secondValuePtr == numeric_limits<double>::quiet_NaN()))
	{
		result = numeric_limits<double>::quiet_NaN();
		return;
	}

	switch (operand)
	{
	case Operations::plus:
		result = *firstValuePtr + *secondValuePtr;
		break;
	case Operations::minus:
		result = *firstValuePtr - *secondValuePtr;
		break;
	case Operations::mult:
		result = *firstValuePtr * *secondValuePtr;
		break;
	case Operations::divide:
		if (*secondValuePtr == 0)
		{
			result = 0;
			break;
		}
		result = *firstValuePtr / *secondValuePtr;
		break;
	}
}

bool CCalculator::VariableExists(const string& variableName) const
{
	auto it = m_variables.find(variableName);
	if (it != m_variables.end())
	{
		return true;
	}

	return false;
}

bool CCalculator::FunctionExists(const string& variableName) const
{
	auto it = m_functions.find(variableName);
	if (it != m_functions.end())
	{
		return true;
	}

	return false;
}

bool CCalculator::IsIdNameCorrect(const string& variableName) const
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
	if ((!IsIdNameCorrect(variableName)) || (VariableExists(variableName)))
	{
		return false;
	}

	m_variables.emplace(variableName, numeric_limits<double>::quiet_NaN());
	return true;
}

bool CCalculator::SetVar(pair<string, string> variableInfo)
{
	string variableName = variableInfo.first;
	if (!IsIdNameCorrect(variableName))
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
	}
	catch (exception)
	{
		if (!VariableExists(variableValue))
		{
			return false;
		}

		m_variables[variableName] = m_variables[variableValue];
	}

	return true;
}

boost::optional<double> CCalculator::GetValueByIdName(const string& varName)
{
	auto varIt = m_variables.find(varName);
	if (varIt != m_variables.end())
	{
		return varIt->second;
	}

	auto fnIt = m_functions.find(varName);
	if (fnIt != m_functions.end())
	{
		fnIt->second.Calculate();
		return fnIt->second.result;
	}

	return boost::none;
}

map<string, double> CCalculator::GetVars() const
{
	return m_variables;
}

map<string, SFunctionData> CCalculator::GetFunctions()
{
	for (auto& item : m_functions)
	{
		item.second.Calculate();
	}
	return m_functions;
}

double* CCalculator::GetPointerToValue(const string& varName)
{
	auto varPtr = m_variables.find(varName);
	if (varPtr != m_variables.end())
	{
		return &varPtr->second;
	}

	auto funcPtr = m_functions.find(varName);
	if (funcPtr != m_functions.end())
	{
		funcPtr->second.Calculate();
		return &funcPtr->second.result;
	}

	return NULL;
}

bool CCalculator::SetFunction(string& functionName, string& firstValue, string& secondValue, Operations& operand)
{
	if (!IsIdNameCorrect(functionName))
	{
		return false;
	}

	if (FunctionExists(functionName))
	{
		return false;
	}

	SFunctionData function;

	if (operand == Operations::none)
	{
		auto ptr = GetPointerToValue(firstValue);
		if (ptr != NULL)
		{
			function.firstValuePtr = ptr;
			function.result = *function.firstValuePtr;

			m_functions.emplace(functionName, function);
			return true;
		}

		return false;
	}

	auto firstValuePtr = GetPointerToValue(firstValue);
	if (firstValuePtr == NULL)
	{
		return false;
	}
	function.firstValuePtr = firstValuePtr;

	auto secondValuePtr = GetPointerToValue(secondValue);
	if (secondValuePtr == NULL)
	{
		return false;
	}
	function.secondValuePtr = secondValuePtr;

	function.operand = operand;

	m_functions.emplace(functionName, function);
	return true;
}
