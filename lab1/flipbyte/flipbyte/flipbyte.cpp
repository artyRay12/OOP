#include <iostream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <bitset>
#include <optional>
using namespace std;


bool IsCorrectNumber(const string str)
{

	if ((stoi(str) > 255) || (stoi(str) < 0))
	{
		return false;
	}

	return true;
}

optional<uint8_t> ParseCommandLine(int argc, char* argv[])
{
	size_t pos;
	string test = argv[1];
	if (argc != 2)
	{
		cout << "Invalid arguments count \n Usage: flipbyte.exe <number>";
		return 1;
	}

	try
	{
		test = stoi(argv[1], &pos);
	}
	catch (const exception & err)
	{
		cout << err.what();
		return nullopt;
	}

	if (*pos != (test.size()))
	{
		return nullopt;
	}

	return static_cast<optional<uint8_t>>(stoi(test));
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
	auto byte = ParseCommandLine(argc, argv);
	cout << "Output: " << static_cast<int>(FlipByte(stoi(argv[1]))) << endl;
	return 0;
}
