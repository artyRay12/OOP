#pragma once
#include "Body.h"

class CVolumetricShapes : public CBody
{
public:
	CVolumetricShapes(const std::string& type, const double density);
	double GetMass() const;
};
