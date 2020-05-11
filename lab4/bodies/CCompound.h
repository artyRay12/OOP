#pragma once
#include "Body.h"
#include <vector>


class CCompound : public CBody
{
public: 
	CCompound();
	double GetVolume() const;
	double GetMass() const;
	double GetDensity() const;

	bool AddChild(std::unique_ptr<CBody> child);

private:
	void AppendProperties(std::ostream& out) const;
	std::vector<std::unique_ptr<CBody>> m_children;


};
