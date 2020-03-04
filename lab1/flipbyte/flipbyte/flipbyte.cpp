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

optional<int> ParseCommandLine(int argc, char* argv[])
{
	size_t pos = 0;
	optional<int> num = 0;

	if (argc != 2)
	{
		return nullopt;
	}

	string numberLength = argv[1];

	try
	{
		num = stoi(argv[1], &pos);
	}
	catch (const exception & err)
	{
		cout << err.what() << endl;;
		return nullopt;
	}


	if (pos != numberLength.length())
	{
		return nullopt;
	}

	if ((num > 255) || (num < 0))
	{
		return nullopt;
	}


	return num;
}

uint8_t GetFlippedByte(uint8_t num)
{
	uint8_t flippedNumber = 0;
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
	if (!byte)
	{
		cout << "Invalid argument! \n Usage: flipbyte.exe <number 0..255>\n";
		return 1;
	}

	cout << "Output: " << static_cast<int>(GetFlippedByte(static_cast<uint8_t>(byte.value()))) << endl;
	return 0;
}