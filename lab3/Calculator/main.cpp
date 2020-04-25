#include "CCalcControl.h"
#include "CCalculator.h"
#include <iostream>

using namespace std;

int main()
{
	CCalculator calc;
	CCalcControl calcControl(calc, cin, cout);
	
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		calcControl.CalculatorDialog();
	}
		
		
}
