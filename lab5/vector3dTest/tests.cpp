#include "lab5/vector3d/CVector3D.h"
#include <catch2/catch.hpp>
using namespace std;

TEST_CASE("operator '-' should return reverse vector")
{
	CVector3D v(1, 1, 1);
	CVector3D reverseV(-1, -1, -1);
	v = -v;
	CHECK(v == reverseV);
}

TEST_CASE("operator '+' should return new vector of sum")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(-1, -1, -1);
	CVector3D resultV;
	auto v3 = v1 + v2;
	CHECK(resultV == v3);
}

TEST_CASE("operator '-' should return new vector of sub")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(1, 1, 1);
	CVector3D resultV;
	auto v3 = v1 - v2;
	CHECK(resultV == v3);
}

TEST_CASE("operator '+=' should change vector whom already exist")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(-1, -1, -1);
	CVector3D resultV;
	v1 += v2;
	CHECK(resultV == v1);
}

TEST_CASE("operator '-=' should change vector whom already exist")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(1, 1, 1);
	CVector3D resultV;
	v1 -= v2;
	CHECK(resultV == v1);
}

TEST_CASE("operator '*' should mult vector to scalar, and return new vector")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(5, 5, 5);
	auto multyV = v1 * 5;
	CHECK(multyV == v2);
}

TEST_CASE("operator '*' should mult scalar to vector")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(5, 5, 5);
	auto multyV = 5 * v1;
	CHECK(multyV == v2);
}

TEST_CASE("operator '/' should div vector to scalar, return new vector")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(5, 5, 5);
	auto divV = v2 / 5;
	CHECK(divV == v1);
}

TEST_CASE("operator '/' should div vector to scalar, change vector whom already exist")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(5, 5, 5);
	v2 /= 5;
	CHECK(v2 == v1);
}

TEST_CASE("operator '!=' compare two vector")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(2, 1, 1);
	CHECK(v1 != v2);
}

TEST_CASE("DotProduct() calculate Dot product of two vectors")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(2, 2, 2);
	CHECK(DotProduct(v1, v2) == 6);
}

TEST_CASE("CrossProduct() calculate Cross product of two vectors")
{
	CVector3D v1(1, 1, 1);
	CVector3D v2(2, 2, 2);
	CVector3D crossProductV(0, 0, 0);
	CHECK(CrossProduct(v1, v2) == crossProductV);
}
