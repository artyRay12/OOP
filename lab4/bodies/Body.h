#pragma once
#include <string>
#include <sstream>
#include <iomanip>

class CBody
{
public:
	CBody(const std::string& type);
	virtual ~CBody();

	 virtual double GetDensity() const = 0;
	 virtual double GetMass() const = 0;
	 virtual double GetVolume() const = 0;

	 std::string GetType();
	
	std::string ToString() const;

private:
	virtual void AppendProperties(std::ostream& strm) const = 0;
	double m_density;
	std::string m_type;
};
