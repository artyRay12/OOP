#include <iostream>
#include <windows.h>
#include "commandHint.h"

using namespace std;

void PrintHint()
{
	cout << "You aslo can use abbreviations!\n";
	cout << "TurnOn - On             |   TurnOff - Off\n";
	cout << "SelectChannel - SC      |   SelectPreviousChannel - SPC\n";
	cout << "GetChannelName - GCN    |   GetChannelByName - GCBN\n";
	cout << "DeleteChannel - DL      |   Info - ?\n";
}
