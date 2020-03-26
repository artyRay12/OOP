#include "htmlEncode/htmlEncode/htmlEncoder.h"
#include <catch2/catch.hpp>
#include <iostream>

using namespace std;

TEST_CASE("htmlEncode should return min element from vector")
{

	/*empty string*/
	string emptyStr;
	CHECK(HtmlEncode(emptyStr) == emptyStr);

	/*not Empty input*/
	string str = "2 < 3 && 3 > 2";
	string encodedStr = "2 &lt 3 &amp&amp 3 &gt 2";
	CHECK(HtmlEncode(str) == encodedStr);
}
