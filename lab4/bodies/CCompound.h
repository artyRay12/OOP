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

	bool AddChild(std::shared_ptr<CBody> child);
private:
	void AppendProperties(std::ostream& output) const;
	std::vector<std::shared_ptr<CBody>> m_children;

};
