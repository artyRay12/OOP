#pragma once
#include "CVolumetricShapes.h"

class CBody;
class CSphere final : public CVolumetricShapes
{
public:
	CSphere(double density, double radius);

	double GetRadius() const;
	double GetVolume() const override;

private:
	void AppendProperties(std::ostream& strm) const override;
	double m_radius;
};
