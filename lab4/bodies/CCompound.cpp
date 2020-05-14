#include "CCompound.h"
#include <iostream>
using namespace std;

CCompound::CCompound()
	: CBody("Compound")
{
}

double CCompound::GetDensity() const
{
	double density = 0;
	for (const shared_ptr<CBody> &body : m_children)
	{
		density += body->GetDensity();
	}
	
	return density / m_children.size();
}


double CCompound::GetVolume() const
{
	double volume = 0;
	for (const shared_ptr<CBody> &body : m_children)
	{
		volume += body->GetVolume();
	}

	return volume;
}

double CCompound::GetMass() const
{
	double mass = 0;
	for (const shared_ptr<CBody> &body : m_children)
	{
		mass += body->GetMass();
	}

	return mass;
}

bool CCompound::AddChild(shared_ptr<CBody> child)
{
	m_children.push_back(child);
	return true;
}

void CCompound::AppendProperties(ostream& output) const
{
	output << "\tConsists of: ";
	for (auto ptr : m_children)
	{
		output << ptr->GetType() << " ";
	}
	output << endl;
}