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

void FlipByte(uint8_t& byte)
{
	byte = ((byte & 0b10101010) >> 1) | ((byte & 0b01010101) << 1);
	//cout << "            " << bitset<8>(byte) << endl;
	byte = ((byte & 0b11001100) >> 2) | ((byte & 0b00110011) << 2);
	//cout << "            " << bitset<8>(byte) << endl;
	byte = (byte << 4) | (byte >> 4);
	//cout << "            " << bitset<8>(byte) << endl;
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

	uint8_t byte = stoi(argv[1]);
	cout << "Input: " << int(byte) << endl;
	FlipByte(byte);
	cout << "Output: " << static_cast<int>(byte) << endl;
	return 0;
}
