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
	vector<float> notEmptyVector = { 1.24f, 2.12f, 3.0f };
	CHECK(ReadVector(notEmptyStream) == notEmptyVector);

	/*Input with extra blanks*/
	string strWithExptraBlanks = "        1.24    2.12       3";
	stringstream extraBlanksStream(strWithExptraBlanks);
	vector<float> extraBlanksVector = { 1.24f, 2.12f, 3.0f };
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
	vector<float> inputVector = { 2.2f, 2.25f, 1.1f, 0.0f };
	vector<float> outputVecor = { 4.4f, 4.5f, 2.2f, 0.0f };
	float number = 2;
	CHECK(MultiplyVectorByNumber(inputVector, number) == outputVecor);
}

TEST_CASE("GetSortVecor() should return sorted vector")
{
	vector<float> notSortedVector = { 3.25f, 2.25f, 1.0f, 0.5f, 2.5f };
	vector<float> sortedVector = {0.5f, 1.0f, 2.25f, 2.5f, 3.25f};
	CHECK(GetSortVector(notSortedVector) == sortedVector);
}


