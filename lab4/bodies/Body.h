#pragma once
#include <string>
#include <sstream>
#include <iomanip>

class CBody
{
public:
	CBody(const std::string& type, double density);
	~CBody();

	 double GetDensity() const;
	 double GetMass() const;
	 virtual double GetVolume() const = 0;
	
	std::string ToString() const;
private:
	//virtual void AppendProperties(std::ostream& strm) const = 0;
	double m_density;
	std::string m_type;
};
