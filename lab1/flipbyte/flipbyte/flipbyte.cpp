#include <iostream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <bitset>
using namespace std;


bool IsCorrectNumber(const string str)
{
	for (int i = 0; i < str.length(); ++i)
	{
		if (!isdigit(str[i])) {
			return false;
		}
	}

	if ((stoi(str) > 255) || (stoi(str) < 0))
	{
		return false;
	}

	return true;
}

unsigned char FlipByte(int num)
{
	unsigned char flippedNumber = 0;
	for (size_t i = 0; i < 8; ++i)
	{
		flippedNumber = flippedNumber << 1;
		flippedNumber = flippedNumber | (num & 0x01);
		num >>= 1;
	}
	return flippedNumber;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count";
		return 1;
	}

	if (!IsCorrectNumber(argv[1]))
	{
		cout << "Value must be 0 .. 255\n";
		return 1;
	}

	cout << "Output: " << static_cast<int>(FlipByte(stoi(argv[1]))) << endl;
	return 0;
}
