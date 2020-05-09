#pragma once

#include "CBodyController.h"
using namespace std;
using namespace std::placeholders;

CBodyController::CBodyController(istream& input, ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actions({
		  /*{ "Sphere", bind(&CBodyControl::AddSphere, this, _1) }, 
		{ "Cone", bind(&CBodyControl::AddCone, this, _1) }, */
		  { "Par", bind(&CBodyController::AddParallelepiped, this, _1) },
		  /*{ "Cylinder", bind(&CBodyControl::AddCylinder, this, _1) }, 
		{ "Show", bind(&CBodyControl::ShowBodies, this, _1) }, 
		{ "ShowMax", bind(&CBodyControl::ShowMax, this, _1) }, 
		{ "ShowLight", bind(&CBodyControl::ShowLight, this, _1) }*/
	  })
{
}

bool CBodyController::HandleCommand()
{
	string command;
	getline(m_input, command);

	stringstream commandStream(command);
	string action;

	commandStream >> action;

	auto it = m_actions.find(action);
	if (it != m_actions.end())
	{
		return it->second(commandStream);
	}
	else
	{
		m_output << "!Error wrong command!\n";
		return false;
	}
}

vector<string> CBodyController::ParseStringToVector(istream& args)
{
	string argsString;
	getline(args, argsString);

	std::istringstream strStream(argsString);
	std::vector<string> parsedArgs((std::istream_iterator<std::string>(strStream)), std::istream_iterator<std::string>());

	return parsedArgs;
}

bool CBodyController::AddParallelepiped(istream& args)
{
	double density, width, height;
	string value;
	auto argsInVector = ParseStringToVector(args);

	try
	{
		density = stod(argsInVector[0]);
		width = stod(argsInVector[1]);
		height = stod(argsInVector[2]);
	}
	catch (exception& e)
	{
		cout << "Error, use numbers as args\n";
		return false;
	}

	m_bodies.emplace_back(make_unique<CParallelepiped>(density, height, width));
	cout << m_bodies[0]->GetDensity();

	return true;
}
