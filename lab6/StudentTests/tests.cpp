#include "lab6/Student/CStudent.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <string>

using namespace std;

void CreateStudentInstance(const string& name, const string& surname, const string& patronymic, size_t age)
{
	CStudent student(name, surname, patronymic, age);
}

TEST_CASE("Create student")
{
	SECTION("all args is good")
	{
		CStudent student("John", "Travolta", "Junior", 35);
		CHECK(student.GetName() == "John");
		CHECK(student.GetSurname() == "Travolta");
		CHECK(student.GetPatronymic() == "Junior");
		CHECK(student.GetAge() == 35);

		INFO("We also can create student without patronymic")
		CStudent student1("Freddie", "Mercury", "", 35);
		CHECK(student1.GetName() == "Freddie");
		CHECK(student1.GetSurname() == "Mercury");
		CHECK(student1.GetPatronymic() == "");
		CHECK(student1.GetAge() == 35);
	}

	SECTION("When name or name is empty, classConstructor should throw logic_error")
	{
		REQUIRE_THROWS_AS(CreateStudentInstance("", "Travolta", "Junior", 35), invalid_argument);
		REQUIRE_THROWS_AS(CreateStudentInstance("John", "", "Junior", 35), invalid_argument);
	}

	SECTION("If age less than 14 or more than 60, classConstructor should throw out_of_range")
	{
		REQUIRE_THROWS_AS(CreateStudentInstance("John", "Travolta", "Junior", 10), out_of_range);
		REQUIRE_THROWS_AS(CreateStudentInstance("John", "Travolta", "Junior", 65), out_of_range);
	}
}

TEST_CASE("Change student")
{
	CStudent student("John", "Travolta", "Junior", 35);

	SECTION("Rename() name and surname can be empty")
	{
		REQUIRE_THROWS_AS(student.Rename("", "Nikolas", "Cage"), invalid_argument);
		REQUIRE_THROWS_AS(student.Rename("Nikolas", "", "Cage"), invalid_argument);
	}

	SECTION("SetAge() name and surname can be empty")
	{
		INFO("NewAge can't be less than currentAge, cuz time");
		REQUIRE_THROWS_AS(student.SetAge(20), domain_error);

		INFO("NewAge should be between [14..60]");
		REQUIRE_THROWS_AS(student.SetAge(120), out_of_range);

		INFO("36 is good arg");
		student.SetAge(36);
		CHECK(student.GetAge() == 36);
	}
}