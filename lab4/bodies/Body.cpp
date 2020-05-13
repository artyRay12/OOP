#include "Body.h"
using namespace std;

CBody::CBody(const string& type, const double density)
	: m_type(type)
	, m_density(density)
{
}

CBody::~CBody()
{
}

string CBody::GetType()
{
	return m_type;
}

double CBody::GetDensity() const
{
	return m_density;
}

string CBody::ToString() const
{
	ostringstream stream;
	stream << m_type << ":"
		   << "density = " << GetDensity() << endl
		   << "\tvolume = " << GetVolume() << endl
		   << "\tmass = " << GetMass() << endl;
	AppendProperties(stream);
	stream << endl;

	return stream.str();
}
