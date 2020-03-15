#include <iostream>
#include <catch2/catch.hpp>
#include "vector-5/sum.h"

using namespace std;

TEST_CASE("Add() must be return sum of two numbers")
{
	CHECK(Add(3, 4) == 7);
}