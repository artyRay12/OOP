#include <iostream>
#include <catch2/catch.hpp>
#include "htmlEncode/htmlEncode/htmlEncoder.h"

using namespace std;

TEST_CASE("ReadString() must be return user input as string")
{
	/*Empty input*/
	istringstream emptyStream;
	string emptyString;
	CHECK(ReadString(emptyStream) == emptyString);

	/*not Empty input*/
	string str = "2 < 3 && 3 > 2";
	istringstream notEmptyStream(str);
	string encodedString 
	CHECK(ReadVector(notEmptyStream) == notEmptyVector);
}

TEST_CASE("GetMinValue() should return min element from vector")
{
	vector<float> inputVector = { 2, 2, 3, 0 };
	float expectedElem = 0;
	CHECK(GetMinValue(inputVector) == expectedElem);
}

TEST_CASE("MultiplyVectorByNumber() should return vector<float> where each element was multyplied by number")
{
	vector<float> inputVector = { 2.2, 2.25, 3, 0 };
	vector<float> outputVecor = { 4.4, 4.5, 6, 0 };
	float number = 2;
	CHECK(MultiplyVectorByNumber(inputVector, number) == outputVecor);
}

TEST_CASE("GetSortVecor() should return sorted vector")
{
	vector<float> notSortedVector = { 3.25, 2.25, 1, 0.5, 2.5 };
	vector<float> sortedVector = { 0.5, 1, 2.25, 2.5, 3.25 };
	CHECK(GetSortVector(notSortedVector) == sortedVector);
}


