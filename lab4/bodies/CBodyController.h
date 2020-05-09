#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>

#include "CParallelepiped.h"
#include "Sphere.h"


class CBodyController
{
public:
	CBodyController(std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool AddParallelepiped(std::istream& args);
	std::vector<std::string> ParseStringToVector(std::istream& args);

	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	ActionMap m_actions;

	using BodiesPtr = std::unique_ptr<CBody>;
	std::vector<BodiesPtr> m_bodies;


};
