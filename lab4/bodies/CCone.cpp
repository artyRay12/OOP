#include "CCone.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

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

void CCone::AppendProperties(ostream& output) const
{
	output << "\tradius = " << GetRadius() << endl;
	output << "\theight = " << GetHeight() << endl;
}