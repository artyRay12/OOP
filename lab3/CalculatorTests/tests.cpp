#include "lab3/Calculator/CCalcControl.h"
#include "lab3/Calculator/CCalculator.h"
#include <catch2/catch.hpp>
#include <sstream>
using namespace std;

stringstream input;
stringstream output;
void SetInput(const string& str, stringstream& stream = input)
{
	stream.clear();
	stream << str;
}

bool IsExist(const string& varName, map<string, double> data)
{
	auto it = data.find(varName);
	if (it != data.end())
	{
		return true;
	}
	return false;
}

boost::optional<double> GetValueFromMap(const string& varName, map<string, double> data)
{
	auto it = data.find(varName);
	if (it != data.end())
	{
		return it->second;
	}
	return boost::none;
}

TEST_CASE("CreateVar() should put new var in map")
{
	CCalculator calc;
	CCalcControl cc(calc, input, cout);
	SECTION("create variable 'x' ")
	{
		SetInput("var x");
		cc.CalculatorDialog();

		CHECK(IsExist("x", calc.GetVars()));
	}

	SECTION("try create variable '1x'")
	{
		SetInput("var 1x");
		cc.CalculatorDialog();

		CHECK(!IsExist("1x", calc.GetVars()));
	}

	SECTION("no args, cant create")
	{
		SetInput("var");
		CHECK(!cc.CalculatorDialog());
	}
}

TEST_CASE("SetVar() should set variable to value")
{
	CCalculator calc;
	CCalcControl cc(calc, input, cout);

	SECTION("SetVar() for variable that doesnt exist, should create new, and set value")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();
		CHECK(GetValueFromMap("x", calc.GetVars()).value() == 5);
	}

	SECTION("SetVar() set variable equal to another variable")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("let y=x");
		cc.CalculatorDialog();

		CHECK(GetValueFromMap("y", calc.GetVars()).value() == 5);
	}

	SECTION("SetVar() set variable equal to variable that doesnt exist")
	{
		SetInput("let y=x");
		cc.CalculatorDialog();

		CHECK(!IsExist("y", calc.GetVars()));
	}

	SECTION("SetVar() for variable that already exist")
	{
		SetInput("var x");
		cc.CalculatorDialog();

		SetInput("let x=5");
		cc.CalculatorDialog();
		CHECK(GetValueFromMap("x", calc.GetVars()).value() == 5);
	}

	SECTION("SetVar() with no args, cant create var or set value")
	{
		SetInput("let x");
		CHECK(!cc.CalculatorDialog());
	}

	SECTION("SetVar() with wrong LHS")
	{
		SetInput("let 1x=5");
		CHECK(!cc.CalculatorDialog());
	}

	SECTION("SetVar() with wrong RHS")
	{
		SetInput("let x=5s");
		CHECK(!cc.CalculatorDialog());
	}
}

TEST_CASE("SetFunction() should calculate Rhs")
{
	CCalculator calc;
	CCalcControl cc(calc, input, cout);

	SECTION("two correct variable in Rhs")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("let y=5");
		cc.CalculatorDialog();

		SetInput("fn sum=x+y");
		cc.CalculatorDialog();

		CHECK(GetValueFromMap("sum", calc.GetFunctions()).value() == 10);
	}

	SECTION("one correct variable in Rhs")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("fn sum=x");
		cc.CalculatorDialog();

		CHECK(GetValueFromMap("sum", calc.GetFunctions()).value() == 5);
	}

	SECTION("uncorrect function name")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("fn 1sum=x");
		cc.CalculatorDialog();

		CHECK(!IsExist("1sum", calc.GetFunctions()));
	}

	SECTION("uncorrect variables in Rhs")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("let y=5");
		cc.CalculatorDialog();

		SetInput("fn sum=x+z");
		cc.CalculatorDialog();

		CHECK(!IsExist("sum", calc.GetFunctions()));
	}

	SECTION("correct one function in Rhs")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("let y=5");
		cc.CalculatorDialog();

		SetInput("fn sum=x+y");
		cc.CalculatorDialog();

		SetInput("fn sum1=sum");
		cc.CalculatorDialog();

		CHECK(GetValueFromMap("sum1", calc.GetFunctions()).value() == 10);
	}

	SECTION("correct two function in Rhs")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("let y=5");
		cc.CalculatorDialog();

		SetInput("fn sum=x+y");
		cc.CalculatorDialog();

		SetInput("fn mult=x*y");
		cc.CalculatorDialog();

		SetInput("fn result=sum+mult");
		cc.CalculatorDialog();

		CHECK(GetValueFromMap("result", calc.GetFunctions()).value() == 35);
	}

	SECTION("ucorrect function in Rhs")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("let y=5");
		cc.CalculatorDialog();

		SetInput("fn sum=x+y");
		cc.CalculatorDialog();

		SetInput("fn result=sum+mult");
		cc.CalculatorDialog();

		CHECK(!IsExist("result", calc.GetFunctions()));
	}

	SECTION("Div by zero")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("let y=0");
		cc.CalculatorDialog();

		SetInput("fn result=x/y");
		cc.CalculatorDialog();

		CHECK(!IsExist("result", calc.GetFunctions()));
	}
}
