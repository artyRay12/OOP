#include "CVector3D.h"
#include <math.h>
using namespace std;

CVector3D::CVector3D()
	: x(0)
	, y(0)
	, z(0)
{
}

CVector3D::CVector3D(double x0, double y0, double z0)
	: x(x0)
	, y(y0)
	, z(z0)
{
}

double CVector3D::GetLength() const
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void CVector3D::Normalize()
{
	double length = GetLength();
	x *= 1 / length;
	y *= 1 / length;
	z *= 1 / length;
}

void CVector3D::Print()
{
	cout << "x = " << x << "\ny = " << y << "\nz = " << z << endl;
}

CVector3D CVector3D::operator+() const
{
	return CVector3D(x, y, z);
}

CVector3D CVector3D::operator-() const
{
	return CVector3D(-x, -y, -z);
}

CVector3D const CVector3D::operator+(CVector3D const& vector2) const
{
	return CVector3D(x + vector2.x, y + vector2.y, z + vector2.z);
}

CVector3D const CVector3D::operator-(CVector3D const& vector2) const
{
	return CVector3D(x - vector2.x, y - vector2.y, z - vector2.z);
}

CVector3D const CVector3D::operator+=(CVector3D const& vector2)
{
	x += vector2.x;
	y += vector2.y;
	z += vector2.z;
	return *this;
}

CVector3D const CVector3D::operator-=(CVector3D const& vector2)
{
	x -= vector2.x;
	y -= vector2.y;
	z -= vector2.z;
	return *this;
}

CVector3D const CVector3D::operator*(double scalar) const
{
	return CVector3D(x * scalar, y * scalar, z * scalar);
}

CVector3D const operator*(double scalar, CVector3D vector)
{
	return vector.operator*(scalar);
}

CVector3D const CVector3D::operator/(double scalar) const
{
	return CVector3D(x / scalar, y / scalar, z / scalar);
}

CVector3D const CVector3D::operator/=(double scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

bool CVector3D::operator==(CVector3D const& vector2) const
{
	return ((x == vector2.x) && (y == vector2.y) && (z == vector2.z));
}

bool CVector3D::operator!=(CVector3D const& vector2) const
{
	return ((x != vector2.x) || (y != vector2.y) || (z != vector2.z));
}

ostream& operator<<(ostream& stream, CVector3D const& vector)
{
	return stream << "x = " << vector.x << "\ny = " << vector.y << "\nz = " << vector.z << endl;
}

istream& operator>>(std::istream& stream, CVector3D& vector)
{
	stream >> vector.x;
	stream >> vector.y;
	stream >> vector.z;

	return stream;
}

double DotProduct(CVector3D const& vector1, CVector3D const& vector2)
{
	return (vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z);
}

CVector3D CrossProduct(CVector3D const& vector1, CVector3D const& vector2)
{
	return (CVector3D(vector1.y * vector2.z - vector1.z * vector2.y, vector1.z * vector2.x - vector1.x * vector2.z, vector1.x * vector2.y - vector1.y * vector2.x));
}