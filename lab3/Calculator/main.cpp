#include "CCalcControl.h"
#include "CCalculator.h"
#include <iostream>

using namespace std;

int main()
{
	CCalculator calc;
	CCalcControl calcControl(calc, cin);
	
	while (1)
	{
		cout << "> ";
		calcControl.CalculatorDialog();
	}
		
		
}
