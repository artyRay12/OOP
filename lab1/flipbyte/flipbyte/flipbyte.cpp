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

optional<uint8_t> ParseCommandLine(int argc, char* argv[])
{
	size_t pos = 0;
	string test = argv[1];
	optional<uint8_t> num = 0;

	if (argc != 2)
	{
		return nullopt;
	}

	try
	{
		num = stoi(argv[1], &pos);
	}
	catch (const exception & err)
	{
		cout << err.what() << endl;;
		return nullopt;
	}

	if (pos != test.length())
	{
		return nullopt;
	}

	if ((stoi(argv[1]) > 255) || (stoi(argv[1]) < 0))
	{
		return nullopt;
	}

	return num;
}

int GetFlippedByte(uint8_t num)
{
	unsigned char flippedNumber = 0;
	for (size_t i = 0; i < 8; ++i)
	{
		flippedNumber = flippedNumber << 1;
		flippedNumber = flippedNumber | (num & 0x01);
		num >>= 1;
	}
	return static_cast<int>(flippedNumber);
}

int main(int argc, char* argv[])
{
	auto byte = ParseCommandLine(argc, argv);
	if (!byte)
	{
		cout << "Invalid argument! \n Usage: flipbyte.exe <number 0..255>\n";
		return 1;
	}

	cout << "Output: " << GetFlippedByte(byte.value()) << endl;
	return 0;
}
