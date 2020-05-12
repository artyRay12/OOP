#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <iterator>

#include <boost/optional.hpp>

#include "CParallelepiped.h"
#include "Sphere.h"
#include "CÑone.h"
#include "CCylinder.h"
#include "CVolumetricShapes.h"
#include "CCompound.h"



class CBodyController
{
public:
	CBodyController(std::istream& input, std::ostream& output);
	bool HandleCommand(std::string str = "");

private:
	bool AddParallelepiped(std::istream& args);
	bool AddSphere(std::istream& args);
	bool AddCone(std::istream& args);
	bool AddCylinder(std::istream& args);
	bool AddCompound(std::istream& args);

	bool PrintBodiesInfo() const;

	boost::optional<std::vector<double>> ParseStringToVector(std::istream& args);

	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actions;

	std::vector<std::shared_ptr<CBody>> m_bodies;


};
