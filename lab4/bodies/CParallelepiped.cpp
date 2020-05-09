#include "CParallelepiped.h"
using namespace std;

CParallelepiped::CParallelepiped(const double density, const double height, const double width)
	: m_width(width)
	, m_height(height)
	, CBody::CBody("parallelipiped", density)
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