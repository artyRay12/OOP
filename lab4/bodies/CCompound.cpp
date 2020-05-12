#include "CCompound.h"
#include <iostream>
using namespace std;

CCompound::CCompound()
	: CBody("compound")
{
}

double CCompound::GetDensity() const
{
	//return GetMass() / GetDensity();
	return 20;
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

bool CCompound::AddChild(shared_ptr<CBody> child)
{
	m_children.push_back(child);
	return true;
}

int CCompound::GetChild() const
{
	return m_children.size();
}

void CCompound::AppendProperties(std::ostream& out) const
{
	for (auto ptr : m_children)
	{
		out << "\t" << ptr->GetType() << endl;
	}
}