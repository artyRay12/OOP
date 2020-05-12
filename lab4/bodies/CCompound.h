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

	int GetChild() const;

private:
	void AppendProperties(std::ostream& out) const;
	std::vector<std::shared_ptr<CBody>> m_children;


};
