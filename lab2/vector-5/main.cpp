#include "vectorUtilities.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
  vector<float> vec = ReadVector(cin);
  MultiplyVectorByNumber(vec, GetMinValue(vec));
  GetSortVector(vec);
  PrintVector(vec);
}
