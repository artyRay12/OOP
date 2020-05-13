#pragma once
#include "CBodyController.h"
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;
using namespace ::placeholders;

CBodyController::CBodyController(istream& input, ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actions({ { make_pair("Par", "Parallelipiped"), bind(&CBodyController::AddParallelepiped, this, _1) },
		  { make_pair("Cyl", "Cylinder"), bind(&CBodyController::AddCylinder, this, _1) },
		  { make_pair("Com", "Compound"), bind(&CBodyController::AddCompound, this, _1) },
		  { make_pair("Sph", "Sphere"), bind(&CBodyController::AddSphere, this, _1) },
		  { make_pair("Cone", "Cone"), bind(&CBodyController::AddCone, this, _1) },
		  { make_pair("Print", "?"), bind(&CBodyController::PrintBodiesInfo, this) },
		  { make_pair("Max", "ShowMax"), bind(&CBodyController::ShowMax, this) },
		  { make_pair("Light", "ShowLight"), bind(&CBodyController::ShowLight, this) } })
{
}

bool CBodyController::HandleCommand(string str)
{
	string command;
	if (str == "")
		getline(m_input, command);
	else
		command = str;

	stringstream commandStream(command);
	string action;

	commandStream >> action;

	auto it = m_actions.begin();
	for (it; it != m_actions.end(); it++)
	{
		if ((it->first.first == action) || (it->first.second == action))
		{
			break;
		}
	}

	if (it != m_actions.end())
	{
		return it->second(commandStream);
	}
	else
	{
		cout << "!! Invalid command\n";
		return false;
	}
}

vector<shared_ptr<CBody>> GetBodies(CBodyController controller)
{
	return controller.m_bodies;
}

optional<vector<double>> CBodyController::ParseStringToVector(istream& args)
{
	string argsString;
	getline(args, argsString);

	istringstream strStream(argsString);
	vector<string> parsedArgs((::istream_iterator<::string>(strStream)), ::istream_iterator<::string>());

	vector<double> parsedArgsDouble;
	try
	{
		transform(parsedArgs.begin(), parsedArgs.end(), ::back_inserter(parsedArgsDouble),
			[](const string& str) { return stod(str); });
	}
	catch (exception& e)
	{
		return nullopt;
	}

	return parsedArgsDouble;
}

bool CBodyController::AddParallelepiped(istream& args)
{
	double density, width, height, depth;

	auto argsInVector = ParseStringToVector(args);
	if ((!argsInVector) || (argsInVector.value().size() != 4))
	{
		cout << "Error! Wrong args, use 4 numbers please!\n";
		return false;
	}

	density = argsInVector.value()[0];
	height = argsInVector.value()[1];
	width = argsInVector.value()[2];
	depth = argsInVector.value()[3];

	m_bodies.push_back(make_shared<CParallelepiped>(density, depth, height, width));

	return true;
}

bool CBodyController::AddSphere(istream& args)
{
	double density, radius;

	auto argsInVector = ParseStringToVector(args);
	if ((!argsInVector) || (argsInVector.value().size() != 2))
	{
		cout << "Error! Wrong args, use 2 numbers please!\n";
		return false;
	}

	density = argsInVector.value()[0];
	radius = argsInVector.value()[1];

	m_bodies.push_back(make_shared<CSphere>(density, radius));

	return true;
}

bool CBodyController::AddCone(istream& args)
{
	double density, radius, height;

	auto argsInVector = ParseStringToVector(args);
	if ((!argsInVector) || (argsInVector.value().size() != 3))
	{
		cout << "Error! Wrong args, use 3 numbers please!\n";
		return false;
	}

	density = argsInVector.value()[0];
	radius = argsInVector.value()[1];
	height = argsInVector.value()[2];

	m_bodies.push_back(make_shared<CCone>(density, radius, height));
	return true;
}

bool CBodyController::AddCylinder(istream& args)
{
	double density, radius, height;

	auto argsInVector = ParseStringToVector(args);
	if ((!argsInVector) || (argsInVector.value().size() != 3))
	{
		cout << "Error! Wrong args, use 3 numbers please!\n";
		return false;
	}

	density = argsInVector.value()[0];
	radius = argsInVector.value()[1];
	height = argsInVector.value()[2];

	m_bodies.push_back(make_shared<CCylinder>(CCylinder(density, radius, height)));

	return true;
}

bool CBodyController::AddCompound(istream& args)
{
	auto body = make_shared<CCompound>(CCompound());
	m_output << "Enter \"done\" if u finish with Compound\n";
	while (1)
	{
		m_output << "Add in Compund:> ";

		string command;
		getline(m_input, command);
		if (command == "done")
		{
			break;
		}
		else
		{
			if (!HandleCommand(command))
			{
				continue;
			}
		}

		body->AddChild(m_bodies[m_bodies.size() - 1]);
		m_bodies.pop_back();
	}

	cout << "Compound added\n";
	m_bodies.push_back(body);
	return true;
}

bool CBodyController::PrintBodiesInfo() const
{
	if (m_bodies.empty())
	{
		cout << "No bodies there\n";
		return false;
	}

	for (int i = 0; i < m_bodies.size(); i++)
	{
		m_output << m_bodies[i]->ToString();
	}

	return true;
}

bool CBodyController::ShowMax() const
{
	if (m_bodies.size() == 0)
	{
		return false;
	}

	double maxWeight = 0;
	shared_ptr<CBody> heaviestBody = nullptr;
	for (shared_ptr<CBody> body : m_bodies)
	{
		if (body->GetMass() > maxWeight)
		{
			maxWeight = body->GetMass();
			heaviestBody = body;
		}
	}

	m_output << heaviestBody->ToString();
	return true;
}

bool CBodyController::ShowLight() const
{
	if (m_bodies.size() == 0)
	{
		return false;
	}

	double minWeight = 0;
	shared_ptr<CBody> lightestBody = nullptr;

	for (shared_ptr<CBody> body : m_bodies)
	{
		double weight = (body->GetDensity() - 1000) * 100 * body->GetVolume();
		if (weight < minWeight)
		{
			minWeight = weight;
			lightestBody = body;
		}
	}

	m_output << lightestBody->ToString();
	return true;
}
