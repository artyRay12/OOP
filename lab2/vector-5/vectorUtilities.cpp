#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>
#include <functional> 
#include <vector>
#include <algorithm>
#include <fstream>
#include "vectorUtilities.h"
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

vector<float> MultiplyVectorByNumber(const vector<float>& vec, float number)
{
    vector<float> multypliedVector;

    for_each(begin(vec), end(vec), [number, &multypliedVector](float vectorElem)
        {
            multypliedVector.push_back(vectorElem * number);
        });

    return multypliedVector;
}


float GetMinValue(const vector<float>& vec)
{

    return *min_element(begin(vec), end(vec));

}

vector<float> GetSortVector(const vector<float>& vec)
{
    vector<float> sortedVector = vec;
    sort(sortedVector.begin(), sortedVector.end());

    return sortedVector;
}

void PrintVector(const vector<float>& vec)
{
    copy(vec.begin(), vec.end(), ostream_iterator<float>(cout, " "));
    cout << endl;
}



vector<float> ReadVectorTest(istream& inputStream)
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
