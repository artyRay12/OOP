#include <iostream>
#include <catch2/catch.hpp>
#include "htmlEncode/htmlEncode/htmlEncoder.h"

using namespace std;

TEST_CASE("ReadString() must be return user input as string")
{
	/*Empty input*/
	string emptyString;
	istringstream emptyStream;
	CHECK(ReadString(emptyStream) == emptyString);

	/*not Empty input*/
	string notEmptyString = "2 < 3 && 3 > 2";
	istringstream notEmptyStream(notEmptyString);
	CHECK(ReadString(notEmptyStream) == notEmptyString);
}

TEST_CASE("htmlEncode should return min element from vector")
{

	/*empty string*/
	string emptyInputString;
	string emptyOutputString;
	HtmlEncode(emptyInputString);
	CHECK(emptyInputString == emptyOutputString);

	/*not Empty input*/
	string notEmptyInputString = "2 < 3 && 3 > 2";
	string notEmptyOutputString = "2 &lt 3 &amp&amp 3 &gt 2";
	HtmlEncode(notEmptyInputString);
	CHECK(notEmptyInputString  == notEmptyOutputString);
}

//TEST_CASE("Replace should insert string instread char")
//{
//	string inputString = "2 > 3";
//	string outputString = "2 &gt 3";
//	replace(inputString)
//}



