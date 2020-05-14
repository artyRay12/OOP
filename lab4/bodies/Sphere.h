#pragma once
#include "CVolumetricShapes.h"

class CSphere final : public CVolumetricShapes
{
public:
	CSphere(const double density, const double radius);

	double GetRadius() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& stream) const override;
	double m_radius;
};
