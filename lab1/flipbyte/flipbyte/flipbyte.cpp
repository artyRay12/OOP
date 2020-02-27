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

using namespace std;

bool IsNumber(const char* str)
{
	for (int i = 0; i < strlen(str); ++i)
	{
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

void FlipByte(uint8_t& byte)
{
	byte = ((byte & 0b10101010) >> 1) | ((byte & 0b01010101) << 1);
	cout << "            " << bitset<8>(byte) << endl;
	byte = ((byte & 0b11001100) >> 2) | ((byte & 0b00110011) << 2);
	cout << "            " << bitset<8>(byte) << endl;
	byte = (byte << 4) | (byte >> 4);
	cout << "            " << bitset<8>(byte) << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n" << "Usage: flipbyte.exe <input byte>\n";
		return 1;
	}



	if ((!IsNumber(argv[1])) || !((stoi(argv[1]) <= 255) && (stoi(argv[1]) >= 0)))
	{
		cout << "Invalid value\n" << "<input byte> must be unsigned int(0 .. 255)\n";
		return 1;
	}

	uint8_t byte = static_cast <uint8_t> (stoi(argv[1]));
	bitset<8> test(stoi(argv[1]));
	cout << "Input byte: " << test << endl;
	FlipByte(byte);
	bitset<8> test1(byte);
	cout << "Output byte: " << static_cast <int> (byte) << "    " << test1 << endl;
	return 0;
}
