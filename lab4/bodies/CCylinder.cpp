#include "CCylinder.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;


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

void CCylinder::AppendProperties(ostream& output) const
{
	output << "\tradius = " << GetRadius() << endl;
	output << "\theight = " << GetHeight() << endl;
}