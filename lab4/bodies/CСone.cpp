#include "CÑone.h"
#include <math.h>

using namespace std;
const double M_PI = 3.14;

CCone::CCone(const double density, const double radius, const double height)
	: CVolumetricShapes::CVolumetricShapes("Cone", density)
	, m_radius(radius)
	, m_height(height)
{
}

double CCone::GetRadius() const
{
	return m_radius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return pow(GetRadius(), 2) * M_PI * GetHeight() / 3;
}

void CCone::AppendProperties(std::ostream& out) const
{
	out << "radius = " << GetRadius() << '\n';
	out << "height = " << GetHeight() << '\n';
}