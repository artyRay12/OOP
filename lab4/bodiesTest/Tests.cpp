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

	SECTION("Parallelipiped <density> <depth> <height> <width>")
	{
		CBodyController control(input, output);
		double density = 1;
		double depth = 2;
		double height = 3;
		double width = 4;
		double volume = 12;
		double mass = 12;

		SetInput("Parallelipiped " + to_string(density) + " " + to_string(depth) + " " + to_string(height) + " " + to_string(width));
		control.HandleCommand();

		SetInput("?");

		output.str(std::string());
		control.HandleCommand();

		stringstream stream;
		stream << "Parallelipiped:"
			   << "density = " << density << endl
			   << "\tvolume = " << volume << endl
			   << "\tmass = " << mass << endl
			   << "\tdepth = " << depth << endl
			   << "\theight = " << height << endl
			   << "\twidth = " << width << endl;

		stream << endl;

		CHECK(output.str() == stream.str());
	}
}

TEST_CASE("Compound consist shapes we test before, and can contain another Compound..recursion hell")
{
	SECTION("Create Compound <= Sphere + Cone")
	{
		CBodyController control(input, output);
		SetInput("Compound\n Sphere 1 2\nCone 1 2 3\ndone"); //esli delat' postro4no togda oshibka :(
		control.HandleCommand();

		SetInput("?");
		output.str(std::string());
		control.HandleCommand();

		stringstream stream;
		stream << "Compound:"
			   << "density = " << 1 << endl
			   << "\tvolume = " << 46.0767 << endl
			   << "\tmass = " << 46.0767 << endl
			   << "\tConsists of: Sphere Cone \n";
		stream << endl;

		CHECK(output.str() == stream.str());
	}

	SECTION("Create Compound <= Compound <= Sphere + Cone, should have same mass and volume")
	{
		CBodyController control(input, output);
		SetInput("Compound\n Compound\n Sphere 1 2\nCone 1 2 3\ndone\ndone");
		control.HandleCommand();

		SetInput("?");
		output.str(std::string());
		control.HandleCommand();

		stringstream stream;
		stream << "Compound:"
			   << "density = " << 1 << endl
			   << "\tvolume = " << 46.0767 << endl
			   << "\tmass = " << 46.0767 << endl
			   << "\tConsists of: Compound \n";
		stream << endl;

		CHECK(output.str() == stream.str());
	}
}

TEST_CASE("ShowMax should print info about haviest body")
{
	CBodyController control(input, output);
	SetInput("Sphere 1 2");
	control.HandleCommand();

	SetInput("Cone 1 2 3");
	control.HandleCommand();

	SetInput("Max");
	output.str(std::string());
	control.HandleCommand();

	stringstream stream;
	stream << "Sphere:"
		   << "density = " << 1 << endl
		   << "\tvolume = " << 33.5103 << endl
		   << "\tmass = " << 33.5103 << endl
		   << "\tradius = " << 2 << endl;
	stream << endl;

	CHECK(output.str() == stream.str());
}

TEST_CASE("Light should print info about haviest body")
{
	CBodyController control(input, output);
	SetInput("Sphere 1 2");
	
	SetInput("Cone 1 2 3");
	control.HandleCommand();
	
	SetInput("Light");
	output.str(std::string());
	control.HandleCommand();

	stringstream stream;
	stream << "Cone:"
		   << "density = " << 1 << endl
		   << "\tvolume = " << 12.5664 << endl
		   << "\tmass = " << 12.5664 << endl
		   << "\tradius = " << 2 << endl
		   << "\theight = " << 3 << endl;
	stream << endl;

	CHECK(output.str() == stream.str());
}
