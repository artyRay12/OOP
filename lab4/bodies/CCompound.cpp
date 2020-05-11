#include "CCompound.h"
#include <iostream>
using namespace std;

CCompound::CCompound()
	: CBody("compound")
{
}

double CCompound::GetDensity() const
{
	return GetMass() / GetDensity();
}

double CCompound::GetVolume() const
{
	double volume = 0;
	return volume;
}

double CCompound::GetMass() const
{
	double mass = 0;
	return mass;
}

bool CCompound::AddChild(unique_ptr<CBody> child)
{
	cout << "Add child " << child->ToString() << endl;
	return false;
}

void CCompound::AppendProperties(std::ostream& out) const
{
}