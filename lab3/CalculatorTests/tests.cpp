#include "lab3/Calculator/CCalcControl.h"
#include "lab3/Calculator/CCalculator.h"
#include <catch2/catch.hpp>
#include <sstream>
using namespace std;

stringstream input;
stringstream output;

void SetInput(const string& str, stringstream& inp = input)
{
	stringstream stream;
	stream << str;
	inp.swap(stream);
}

template <typename T>
bool IsExist(const string& varName, map<string, T> data)
{
	auto it = data.find(varName);
	if (it != data.end())
	{
		return true;
	}
	return false;
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

	SECTION("create two vars with same names")
	{
		SetInput("var x");
		CHECK(cc.CalculatorDialog());

		SetInput("var x");
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

		CHECK(calc.GetValueByIdName("x").value() == 5);
	}

	SECTION("SetVar() set variable equal to another variable")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("let y=x");
		cc.CalculatorDialog();

		CHECK(calc.GetValueByIdName("y").value() == 5);
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
		CHECK(calc.GetValueByIdName("x").value() == 5);
	}

	SECTION("SetVar() with no args, cant create var or set value")
	{
		SetInput("let x");
		CHECK(!IsExist("x", calc.GetVars()));
	}

	SECTION("SetVar() with wrong LHS")
	{
		SetInput("let x*=5");
		CHECK(!IsExist("1x", calc.GetVars()));
	}

	SECTION("SetVar() with wrong RHS")
	{
		SetInput("let x=5s");
		CHECK(!IsExist("x", calc.GetVars()));
	}
}

TEST_CASE("SetFunction() should calculate Rhs")
{
	CCalculator calc;
	CCalcControl cc(calc, input, cout);

	SECTION("two correct variable in Rhs")
	{
		SetInput("let z=5");
		cout << input.str() << endl;
		cc.CalculatorDialog();

		SetInput("let y=5");
		cc.CalculatorDialog();

		SetInput("fn sum=z+y");
		cc.CalculatorDialog();

		CHECK(calc.GetValueByIdName("sum").value() == 10);
	}

	SECTION("one correct variable in Rhs")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("fn f=x");
		cc.CalculatorDialog();

		CHECK(calc.GetValueByIdName("f").value() == 5);
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

		CHECK(calc.GetValueByIdName("sum1").value() == 10);
	}

	SECTION("correct two function in Rhs")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("let y=5");
		cc.CalculatorDialog();

		SetInput("fn sum=x+y");
		cc.CalculatorDialog();
		CHECK(calc.GetValueByIdName("sum").value() == 10);

		SetInput("fn mult=x*y");
		cc.CalculatorDialog();
		CHECK(calc.GetValueByIdName("mult").value() == 25);

		SetInput("fn sub=x-y");
		cc.CalculatorDialog();
		CHECK(calc.GetValueByIdName("sub").value() == 0);

		SetInput("fn div=x/y");
		cc.CalculatorDialog();
		CHECK(calc.GetValueByIdName("div").value() == 1);

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

	SECTION("without Rhs, without '='")
	{
		SetInput("fn result+sum+mult");
		CHECK(!cc.CalculatorDialog());
	}

	SECTION("Div by zero")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("let y=0");
		cc.CalculatorDialog();

		SetInput("fn result=x/y");
		cc.CalculatorDialog();

		CHECK(calc.GetValueByIdName("result").value() == 0);
	}

	SECTION("if variable was changed, function should change too")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("fn result=x");
		cc.CalculatorDialog();

		CHECK(calc.GetValueByIdName("result").value() == 5);

		SetInput("let x=10");
		cc.CalculatorDialog();

		CHECK(calc.GetValueByIdName("result").value() == 10);
	}

	SECTION("if function 'F' was chahed, function 'F2' which use 'F' should change too")
	{
		SetInput("let x=5");
		cc.CalculatorDialog();

		SetInput("fn f=x");
		cc.CalculatorDialog();

		SetInput("fn f1=f");
		cc.CalculatorDialog();

		CHECK(calc.GetValueByIdName("f1").value() == 5);

		SetInput("let x=10");
		cc.CalculatorDialog();
		CHECK(calc.GetValueByIdName("f").value() == 10);
		CHECK(calc.GetValueByIdName("f1").value() == 10);
	}
}
