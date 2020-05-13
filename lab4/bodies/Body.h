#pragma once
#include <string>
#include <sstream>

class CBody
{
public:
	CBody(const std::string& type, const double density = 0);
	virtual ~CBody();

	virtual double GetDensity() const;
	virtual double GetMass() const = 0;
	virtual double GetVolume() const = 0;

	std::string GetType();
	
	std::string ToString() const;

private:
	virtual void AppendProperties(std::ostream& strm) const = 0;
	double m_density;
	std::string m_type;
};
