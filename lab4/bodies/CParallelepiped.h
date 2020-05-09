#pragma once
#include "Body.h"

class CParallelepiped: public CBody
{
public:
	CParallelepiped(double density, double height, double width);
	double GetHeight() const;
	double GetWidth() const;
	double GetVolume() const override;

private:
	const double m_width;
	const double m_height;

};
