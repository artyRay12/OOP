#pragma once
#include "CVolumetricShapes.h"

class CCylinder : public CVolumetricShapes
{
public:
	CCylinder(const double density, const double height, const double radius);
	double GetRadius() const;
	double GetHeight() const;
	double GetVolume() const override;
private:
	void AppendProperties(std::ostream& out) const override;
	double m_radius;
	double m_height;

};
