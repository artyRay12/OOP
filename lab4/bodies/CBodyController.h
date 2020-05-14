#pragma once
#include <functional>
#include <map>
#include <optional>
#include <vector>

#include "CCompound.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CVolumetricShapes.h"
#include "CÑone.h"
#include "Sphere.h"

class CBodyController
{
public:
	CBodyController(std::istream& input, std::ostream& output);
	bool HandleCommand(std::string str = "");

	friend std::vector<std::shared_ptr<CBody>> GetBodies(CBodyController controller); // for tests

private:
	bool AddParallelepiped(std::istream& args);
	bool AddSphere(std::istream& args);
	bool AddCone(std::istream& args);
	bool AddCylinder(std::istream& args);
	bool AddCompound(std::istream& args);

	bool PrintBodiesInfo() const;
	bool ShowMax() const;
	bool ShowLight() const;

	std::optional<std::vector<double>> ParseStringToVector(std::istream& args);

	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::pair<std::string, std::string>, Handler>;
	ActionMap m_actions;

	std::vector<std::shared_ptr<CBody>> m_bodies;
	int compoundLevel = 0;
};
