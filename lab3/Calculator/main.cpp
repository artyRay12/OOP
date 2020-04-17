#include <iostream>
#include "CCalculator.h"
#include "CCalcControl.h"

using namespace std;

int main()
{
	CCalculator calc;
	CCalcControl calcControl(calc, cin);
	calcControl.CalculatorDialog();
}
