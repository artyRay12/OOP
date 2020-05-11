#pragma once
#include "CVolumetricShapes.h"

class CCone : public CVolumetricShapes
{
public:
	CCone(const double density, const double radius, const double height);

	double GetRadius() const;
	double GetHeight() const;

	double GetVolume() const override;
private:
	void AppendProperties(std::ostream& out) const override;
	double m_radius;
	double m_height;
	
};
