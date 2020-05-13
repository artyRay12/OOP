#pragma once
#include "Body.h"

class CVolumetricShapes : public CBody
{
public:
	CVolumetricShapes(const std::string& type, double density);

	double GetMass() const;
	virtual double GetVolume() const = 0;

private:
	virtual void AppendProperties(std::ostream& out) const = 0;
};
