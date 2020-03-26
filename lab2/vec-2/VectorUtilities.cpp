#include "vectorUtilities.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<float> ReadVector(istream& inputStream)
{
	string line;
	vector<float> vec;
	if (getline(inputStream, line))
	{
		stringstream stringIterator(line);
		copy(istream_iterator<float>(stringIterator), istream_iterator<float>(), inserter(vec, vec.end()));
	}

	return vec;
}

void MultiplyVectorByNumber(vector<float>& vec, optional<float> number)
{
	if (number && number != 1)
	{
		for (auto& item : vec)
		{
			item *= number.value();
		}
	}
}

optional<float> GetMinValue(const vector<float>& vec)
{
	if (!vec.empty())
	{
		return *min_element(begin(vec), end(vec));
	}

	return nullopt;
}

void SortVector(vector<float>& vec)
{
	sort(vec.begin(), vec.end());
}

void PrintVector(const vector<float>& vec)
{
	copy(vec.begin(), vec.end(), ostream_iterator<float>(cout, " "));
	cout << endl;
}
