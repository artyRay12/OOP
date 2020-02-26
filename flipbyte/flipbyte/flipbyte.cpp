#include <iostream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    int n;
    cout << "Введите число: ";
    cin >> n;
    for (int i = sizeof(int) * 8; i > -1; --i)
        cout << (n >> i) & 1;
    system("pause");
    return 0;
}

