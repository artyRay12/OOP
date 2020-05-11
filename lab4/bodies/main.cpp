#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "CBodyController.h"

using namespace std;

int main()
{
	CBodyController control(cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "NEW HANDLER\n";
		control.HandleCommand();
	}
}

