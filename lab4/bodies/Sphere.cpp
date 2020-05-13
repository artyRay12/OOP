#include "Sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;


CSphere::CSphere(double density, double radius)
	: CVolumetricShapes::CVolumetricShapes("Sphere", density)
	, m_radius(radius)
{
}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const
{
	return (pow(m_radius, 3) * M_PI) * 4 / 3;
}

void CSphere::AppendProperties(std::ostream& output) const
{
	output << "\tradius = " << GetRadius() << endl;
}
