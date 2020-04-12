// TV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "CTV.h"
#include "CRemoteControl.h"
using namespace std;

int main()
{
	CTV tv;
	CRemoteControl pult(tv);
	pult.CommandHandler();
}