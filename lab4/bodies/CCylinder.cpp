#include "CCylinder.h"
#define _USE_MATH_DEFINES
#include <math.h>



CCylinder::CCylinder(const double density, const double height, const double radius)
	: CVolumetricShapes("cylinder", density)
	, m_height(height)
	, m_radius(radius)
{
}

double CCylinder::GetRadius() const
{
	return m_radius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}
double CCylinder::GetVolume() const
{
	return pow(GetRadius(), 2) * M_PI * GetHeight();
}

void CCylinder::AppendProperties(std::ostream& out) const
{
	out << "radius = " << GetRadius() << '\n';
	out << "height = " << GetHeight() << '\n';
}