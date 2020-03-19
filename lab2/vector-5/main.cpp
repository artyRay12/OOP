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

int main()
{
    vector<float> vec = ReadVector(cin);

    if (!vec.empty())
    {
        PrintVector(GetSortVector(MultiplyVectorByNumber(vec, GetMinValue(vec))));
    }
    else
    {
        PrintVector(vec);
    }
}



