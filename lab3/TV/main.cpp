#include "CRemoteControl.h"
#include "CTV.h"
#include "commandHint.h"
#include <iostream>
using namespace std;

int main()
{
	CTV tv;
	CRemoteControl rc(tv, cin);
	PrintHint();

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		rc.CommandHandler();
	}

	return 0;
}