#include "CVolumetricShapes.h"

using namespace std;

CVolumetricShapes::CVolumetricShapes(const string& type, const double density)
	: CBody(type, density)
{
}

double CVolumetricShapes::GetMass() const
{
	return GetDensity() * GetVolume();
}
