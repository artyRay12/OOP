#include "vec-2/vectorUtilities.h"
#include <catch2/catch.hpp>
#include <iostream>

using namespace std;

TEST_CASE("GetMinValue() should return min element from vector")
{
	vector<float> inputVector = { 0, 2, 3 };
	float expectedElem = 0;
	CHECK(GetMinValue(inputVector) == expectedElem);
}

TEST_CASE("MultiplyVectorByNumber() should return vector<float> where each "
		  "element was multyplied by number")
{

	vector<float> inputVector = { 2.2f, 2.25f, 1.1f, 0.0f };
	vector<float> outputVector = { 4.4f, 4.5f, 2.2f, 0.0f };
	float number = 2;
	MultiplyVectorByNumber(inputVector, number);
	CHECK(inputVector == outputVector);
}

TEST_CASE("GetSortVecor() should return sorted vector")
{
	vector<float> notSortedVector = { 3.25f, 2.25f, 1.0f, 0.5f, 2.5f };
	vector<float> sortedVector = { 0.5f, 1.0f, 2.25f, 2.5f, 3.25f };
	SortVector(notSortedVector);
	CHECK(notSortedVector == sortedVector);
}
