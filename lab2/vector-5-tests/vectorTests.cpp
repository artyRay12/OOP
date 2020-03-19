#include <iostream>
#include <catch2/catch.hpp>
#include "vector-5/vectorUtilities.h"

using namespace std;

TEST_CASE("ReadVector() must be return vector<float>")
{
	/*Empty input*/
	stringstream emptyStream;
	vector<float> emptyVector;
	CHECK(ReadVector(emptyStream) == emptyVector);

	/*not Empty input*/
	string str = "1.24 2.12 3";
	stringstream notEmptyStream(str);
	vector<float> notEmptyVector = { 1.24, 2.12, 3.0 };
	CHECK(ReadVector(notEmptyStream) == notEmptyVector);

	/*Input with extra blanks*/
	string strWithExptraBlanks = "        1.24    2.12       3";
	stringstream extraBlanksStream(strWithExptraBlanks);
	vector<float> extraBlanksVector = { 1.24, 2.12, 3.0 };
	CHECK(ReadVector(extraBlanksStream) == extraBlanksVector);
}

TEST_CASE("GetMinValue() should return min element from vector")
{
	vector<float> inputVector = { 0, 2, 3};
	float expectedElem = 0;
	CHECK(GetMinValue(inputVector) == expectedElem);
}

TEST_CASE("MultiplyVectorByNumber() should return vector<float> where each element was multyplied by number")
{
	vector<float> inputVector = { 2.2, 2.25, 1.1, 0.0 };
	vector<float> outputVecor = { 4.4, 4.5, 2.2, 0 };
	float number = 2;
	CHECK(MultiplyVectorByNumber(inputVector, number) == outputVecor);
}

TEST_CASE("GetSortVecor() should return sorted vector")
{
	vector<float> notSortedVector = { 3.25, 2.25, 1, 0.5, 2.5 };
	vector<float> sortedVector = {0.5, 1, 2.25, 2.5, 3.25 };
	CHECK(GetSortVector(notSortedVector) == sortedVector);
}


