#include "CStudent.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

int main()
{
	size_t age;
	string name, surname, patronymic;


	while (!cin.eof() && !cin.fail())
	{
		if (!((cin >> name) && (cin >> surname) && (cin >> patronymic) && (cin >> age)))
		{
			cout << "Unknown command!" << endl;
		}
		else
		{
			try
			{
				CStudent st(boost::trim_copy(name), boost::trim_copy(surname), boost::trim_copy(patronymic), age);
			}
			catch (const invalid_argument& e)
			{
				cout << e.what();
			}
			catch (const out_of_range& e)
			{
				cout << e.what();
			}
		}
	}

	return 0;
}
