#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> vec{ 0, 1, 2, 3 };
	int* p = &vec[0];

	cout << "p = " << *p << endl;

	vec[0] = 1;

	cout << "p = " << *p << endl;

}

