#include "CParallelepiped.h"
#include <iostream>
using namespace std;

CParallelepiped::CParallelepiped(const double density, const double depth, const double height, const double width)
	: m_width(width)
	, m_height(height)
	, m_depth(depth)
	, CVolumetricShapes::CVolumetricShapes("Parallelipiped", density)
{
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetVolume() const
{
	return GetWidth() * GetHeight();
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

void CParallelepiped::AppendProperties(ostream& output) const
{
	output << "\tdepth = " << GetDepth() << endl;
	output << "\theight = " << GetHeight() << endl;
	output << "\twidth = " << GetWidth() << endl;
}