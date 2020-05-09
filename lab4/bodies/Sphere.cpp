#include "Sphere.h"
#include <cmath>
#define M_PI 3.14

CSphere::CSphere(double density, double radius)
	: CBody("Sphere", density)
	, m_radius(radius)
{
}

double CSphere::GetRadius()const
{
	return m_radius;
}

double CSphere::GetVolume()const
{
	return (pow(m_radius, 3) * M_PI) * 4 / 3;
}

//void CSphere::AppendProperties(std::ostream & strm) const
//{
//	strm << "\tradius = " << GetRadius() << std::endl;
//}
