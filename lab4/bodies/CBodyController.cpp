#pragma once

#include "CBodyController.h"

using namespace std;
using namespace std::placeholders;

CBodyController::CBodyController(istream& input, ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actions({
		  { "Sph", bind(&CBodyController::AddSphere, this, _1) },
		  { "Cone", bind(&CBodyController::AddCone, this, _1) },
		  { "Par", bind(&CBodyController::AddParallelepiped, this, _1) },
		  { "Cyl", bind(&CBodyController::AddCylinder, this, _1) },
		  { "Print", bind(&CBodyController::PrintBodiesInfo, this) },
		  { "Comp", bind(&CBodyController::AddCompound, this, _1) }
		  /*{ "ShowMax", bind(&CBodyControl::ShowMax, this, _1) }, 
		{ "ShowLight", bind(&CBodyControl::ShowLight, this, _1) }*/
	  })
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

boost::optional<vector<double>> CBodyController::ParseStringToVector(istream& args)
{
	string argsString;
	getline(args, argsString);

	istringstream strStream(argsString);
	vector<string> parsedArgs((std::istream_iterator<std::string>(strStream)), std::istream_iterator<std::string>());

	vector<double> parsedArgsDouble;
	try
	{
		transform(parsedArgs.begin(), parsedArgs.end(), std::back_inserter(parsedArgsDouble),
			[](const string& str) { return stod(str); });
	}
	catch (exception& e)
	{
		return boost::none;
	}

	//copy(parsedArgsDouble.begin(), parsedArgsDouble.end(), std::ostream_iterator<double>(cout, ", "));

	return parsedArgsDouble;
}

bool CBodyController::AddParallelepiped(istream& args)
{
	double density, width, height, depth;

	auto argsInVector = ParseStringToVector(args);
	if (!argsInVector)
	{
		cout << "Error! Use numbers as args\n";
		return false;
	}

	density = argsInVector.value()[0];
	height = argsInVector.value()[1];
	width = argsInVector.value()[2];
	depth = argsInVector.value()[3];

	m_bodies.push_back(make_shared<CParallelepiped>(density, depth, height, width));

	return true;
}

bool CBodyController::AddSphere(std::istream& args)
{
	double density, radius;

	auto argsInVector = ParseStringToVector(args);
	if (!argsInVector)
	{
		cout << "Error! Use numbers as args\n";
		return false;
	}

	density = argsInVector.value()[0];
	radius = argsInVector.value()[1];

	m_bodies.push_back(make_shared<CSphere>(density, radius));

	return true;
}

bool CBodyController::AddCone(std::istream& args)
{
	double density, radius, height;

	auto argsInVector = ParseStringToVector(args);
	if (!argsInVector)
	{
		cout << "Error! Use numbers as args\n";
		return false;
	}

	density = argsInVector.value()[0];
	radius = argsInVector.value()[1];
	height = argsInVector.value()[2];

	m_bodies.emplace_back(make_shared<CCone>(density, radius, height));
	return true;
}

bool CBodyController::AddCylinder(std::istream& args)
{
	double density, radius, height;

	auto argsInVector = ParseStringToVector(args);
	if (!argsInVector)
	{
		cout << "Error! Use numbers as args\n";
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
	m_output << "Enter the figures for Compund\n";
	auto body = make_shared<CCompound>(CCompound());
	while (1)
	{
		//m_output << "Compound cycle\n";

		string command;
		getline(m_input, command);
		if (command == "done")
		{
			break;
		}

		HandleCommand(command);

		body->AddChild(m_bodies[m_bodies.size() - 1]);
		m_bodies.pop_back();

		//cout << body->GetChild() << endl;
	}

	//cout << "ADDED " << body->GetChild() << " ELEMENTS IN COMPOUND" << endl;
	m_bodies.push_back(body);
	return true;
}

bool CBodyController::PrintBodiesInfo() const
{
	if (m_bodies.empty())
	{
		cout << "empty bodies\n";
		return false;
	}

	for (int i = 0; i < m_bodies.size(); i++)
	{
		m_output << m_bodies[i]->ToString();
	}

	//m_output << m_bodies.size() << endl;

	return true;
}
