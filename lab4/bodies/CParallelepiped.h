#pragma once
#include "CVolumetricShapes.h"

class CParallelepiped: public CVolumetricShapes
{
public:
	CParallelepiped(const double density, const double depth, const double height, const double width);

	double GetHeight() const;
	double GetWidth() const;
	double GetDepth() const;

	double GetVolume() const override;
private:
	void AppendProperties(std::ostream& output) const;
	const double m_width;
	const double m_height;
	const double m_depth;

};
