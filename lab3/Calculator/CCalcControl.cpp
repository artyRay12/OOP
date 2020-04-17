#include "CCalcControl.h"
using namespace std;
using namespace std::placeholders;

CCalcControl::CCalcControl(CCalculator calculator, istream& input)
	: m_calc(calculator)
	, m_input(input)
	, m_actions({
		{ "var", bind(&CCalcControl::SetVar, this, _1) },/*
		{ "let", bind(&CCalcControl::LetVarValue, this, _1) },
		{ "fn", bind(&CCalcControl::SetFunction, this, _1) },
		{ "print", bind(&CCalcControl::PrintIdentifierValue, this, _1) },
		{ "printvars", bind(&CCalcControl::PrintVariables, this) },
		{ "printfns", bind(&CCalcControl::PrintFunctions, this) } */
	  })
{
}

bool CCalcControl::CalculatorDialog()
{
	string action;
	m_input >> action;

	auto it = m_actions.find(action);
	if (it == m_actions.end())
	{
		
	}

	return true;
}

bool CCalcControl::SetVar(istream& arg)
{
	string variableName;
	arg >> variableName;
	return true;
}
