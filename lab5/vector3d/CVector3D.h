#pragma once
#include <iostream>
class CVector3D
{
public:
	CVector3D();
	CVector3D(double x0, double y0, double z0);

	double GetLength() const;
	void Normalize();
	void Print();

	CVector3D operator-() const;
	CVector3D operator+() const;

	CVector3D const operator+(CVector3D const& vector2) const;
	CVector3D const operator-(CVector3D const& vector2) const;

	CVector3D const operator+=(CVector3D const& vector2);
	CVector3D const operator-=(CVector3D const& vector2);

	CVector3D const operator*(double scalar) const;

	CVector3D const operator/(double scalar) const;
	CVector3D const operator/=(double scalar);

	bool operator==(CVector3D const& operand2) const;
	bool operator!=(CVector3D const& operand2) const;
	
	double x, y, z;
};

CVector3D const operator*(double scalar, CVector3D vector);
std::ostream& operator<<(std::ostream& stream, CVector3D const& vector);
std::istream& operator>>(std::istream& stream, CVector3D& vector);
double DotProduct(CVector3D const& v1, CVector3D const& v2);
CVector3D CrossProduct(CVector3D const& v1, CVector3D const& v2);
