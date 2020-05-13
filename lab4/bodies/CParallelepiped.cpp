#include "CParallelepiped.h"
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

void CParallelepiped::AppendProperties(ostream& out) const
{
	out << "\twidth = " << GetWidth() << endl;
	out << "\theight = " << GetHeight() << endl;
	out << "\tdepth = " << GetDepth() << endl;
}