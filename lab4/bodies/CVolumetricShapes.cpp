#include "CVolumetricShapes.h"

using namespace std;

CVolumetricShapes::CVolumetricShapes(const string& type, double density)
	: CBody(type)
	, m_density(density)
{
}

double CVolumetricShapes::GetDensity() const
{
	return m_density;
}

double CVolumetricShapes::GetMass() const
{
	return GetDensity() * GetVolume();
}
