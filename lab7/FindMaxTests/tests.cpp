#include "lab7/FindMax/FindMax.h"
#include <catch2/catch.hpp>
#include <vector>
using namespace std;

TEST_CASE("FindMax(vector<T> const& arr, T& maxValue) should change maxValue to max elem of arr and return 'true', if arr empty return 'false' ")
{
	SECTION("FindMax get empty arr")
	{
		int maxValue;
		vector<int> arr = {};
		CHECK(!FindMax(arr, maxValue));
	}

	SECTION("FindMax get arr of ints")
	{
		int maxValue;
		vector<int> arr = { 0, 10, 2 };
		REQUIRE(FindMax(arr, maxValue));
		CHECK(maxValue == 10);
	}

	SECTION("FindMax get arr of size_t")
	{
		size_t maxValue;
		vector<size_t> arr = { 0, 10, 2, 5 };
		REQUIRE(FindMax(arr, maxValue));
		CHECK(maxValue == 10);
	}

	SECTION("FindMax get arr of doubles")
	{
		double maxValue;
		vector<double> arr = { 0.5, 10.12, 2.299, 10.2 };
		REQUIRE(FindMax(arr, maxValue));
		CHECK(maxValue == 10.2);
	}

	SECTION("FindMax get arr of string")
	{
		string maxValue;
		vector<string> arr = { "str", "string", "stringButBigger" };
		REQUIRE(FindMax(arr, maxValue));
		CHECK(maxValue == "stringButBigger");
	}
}

TEST_CASE("FindMax<const char*>(vector<const char*> const& arr, const char*& maxValue) work same but only with const char*")
{
	SECTION("arr is empty")
	{
		const char* maxValue;
		vector<const char*> arr = {};
		CHECK(!FindMax(arr, maxValue));
	}

	SECTION("arr not empty")
	{
		const char* maxValue;
		vector<const char*> arr = {"imChar", "meToo", "zZzZ"};
		REQUIRE(FindMax(arr, maxValue));
		CHECK(maxValue == "zZzZ");
	}
}