#include <catch2/catch.hpp>

#include "lab4/bodies/Body.h"
#include "lab4/bodies/CBodyController.h"
#include "lab4/bodies/CCompound.h"
#include "lab4/bodies/CCylinder.h"
#include "lab4/bodies/CParallelepiped.h"
#include "lab4/bodies/CVolumetricShapes.h"
#include "lab4/bodies/CÑone.h"
#include "lab4/bodies/Sphere.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include <array>
#include <iostream>
#include <sstream>

using namespace std;

stringstream input;
stringstream output;
void SetInput(const string& str, stringstream& inp = input)
{
	stringstream stream;
	stream << str;
	inp.swap(stream);
}

TEST_CASE("Sphere <num> <num> should create Sphere")
{
	CBodyController control(input, output);
	SECTION("Too much args for Sphere")
	{
		SetInput("Sphere 20 20 20");
		control.HandleCommand();
		CHECK(GetBodies(control).size() == 0);
	}

	SECTION("Not enough args for Sphere")
	{
		SetInput("Sphere 20");
		control.HandleCommand();
		CHECK(GetBodies(control).size() == 0);
	}

	SECTION("Wrong args for Sphere")
	{
		SetInput("Sphere 30 arg");
		control.HandleCommand();
		CHECK(GetBodies(control).size() == 0);
	}

	SECTION("All good")
	{
		SetInput("Sphere 20 20");
		control.HandleCommand();

		REQUIRE(GetBodies(control).size() != 0);
		CHECK(GetBodies(control)[0]->GetType() == "Sphere");
	}
}

TEST_CASE("Cylinder And Cone need 3 arg for creating")
{
	CBodyController control(input, output);
	string bodyNames[2] = { "Cylinder", "Cone" };

	for (string name : bodyNames)
	{
		SECTION("Too much args")
		{
			SetInput(name + " 20 20 20 20");
			control.HandleCommand();
			CHECK(GetBodies(control).size() == 0);
		}

		SECTION("Not enough args")
		{
			SetInput(name + " 20 20");
			control.HandleCommand();
			CHECK(GetBodies(control).size() == 0);
		}

		SECTION("Wrong args")
		{
			SetInput(name + " 30 arg arg1");
			control.HandleCommand();
			CHECK(GetBodies(control).size() == 0);
		}

		SECTION("All good")
		{
			SetInput(name + " 20 20 20");
			control.HandleCommand();

			REQUIRE(GetBodies(control).size() != 0);
			CHECK(GetBodies(control)[0]->GetType() == name);
		}
	}
}

TEST_CASE("Parallelipiped need 4 args for creating")
{
	CBodyController control(input, output);
	SECTION("Too much args")
	{
		SetInput("Parallelipiped 20 20 20 20 20");
		control.HandleCommand();
		CHECK(GetBodies(control).size() == 0);
	}

	SECTION("Not enough args")
	{
		SetInput("Parallelipiped 20 20 20");
		control.HandleCommand();
		CHECK(GetBodies(control).size() == 0);
	}

	SECTION("Wrong args")
	{
		SetInput("Parallelipiped 30 arg arg1 12ar");
		control.HandleCommand();
		CHECK(GetBodies(control).size() == 0);
	}

	SECTION("All good")
	{
		SetInput("Parallelipiped 20 20 20 20");
		control.HandleCommand();

		REQUIRE(GetBodies(control).size() != 0);
		CHECK(GetBodies(control)[0]->GetType() == "Parallelipiped");
	}
}

TEST_CASE("Properties test")
{
	

	SECTION("Sphere <density> <radius>")
	{
		CBodyController control(input, output);
		double density = 20;
		double radius = 20;
		double volume = 33510.3;
		double mass = 670206;

		SetInput("Sphere " + to_string(density) + " " + to_string(radius));
		control.HandleCommand();

		SetInput("?");
		INFO("? - print info about all bodies, and now its only Sphere");
		control.HandleCommand();

		stringstream stream;
		stream << "Sphere:"
			   << "density = " << density << endl
			   << "\tvolume = " << volume << endl
			   << "\tmass = " << mass << endl
			   << "\tradius = " << radius << endl;
		stream << endl;

		CHECK(output.str() == stream.str());
	}

	SECTION("Cylinder <density> <radius> <height>")
	{
		CBodyController control(input, output);
		double density = 20;
		double radius = 20;
		double height = 20;
		double volume = 25132.7;
		double mass = 502655;

		SetInput("Cylinder " + to_string(density) + " " + to_string(radius) + " " + to_string(height));
		control.HandleCommand();

		SetInput("?");

		output.str(std::string());
		control.HandleCommand();

		stringstream stream;
		stream << "Cylinder:"
			   << "density = " << density << endl
			   << "\tvolume = " << volume << endl
			   << "\tmass = " << mass << endl
			   << "\tradius = " << radius << endl
			   << "\theight = " << height << endl;
		stream << endl;

		CHECK(output.str() == stream.str());
	}

	SECTION("Cone <density> <radius> <height>")
	{
		CBodyController control(input, output);
		double density = 20;
		double radius = 20;
		double height = 20;
		double volume = 8377.58;
		double mass = 167552;

		SetInput("Cone " + to_string(density) + " " + to_string(radius) + " " + to_string(height));
		control.HandleCommand();

		SetInput("?");

		output.str(std::string());
		control.HandleCommand();

		stringstream stream;
		stream << "Cone:"
			   << "density = " << density << endl
			   << "\tvolume = " << volume << endl
			   << "\tmass = " << mass << endl
			   << "\tradius = " << radius << endl
			   << "\theight = " << height << endl;
		stream << endl;

		CHECK(output.str() == stream.str());
	}
}