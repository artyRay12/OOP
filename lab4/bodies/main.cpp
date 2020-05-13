#include <iostream>
#include "CBodyController.h"

using namespace std;

int main()
{
	CBodyController control(cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		control.HandleCommand();
	}
}

