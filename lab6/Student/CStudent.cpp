#include "CStudent.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <stdexcept>
using namespace std;

CStudent::CStudent(const string& name, const string& surname, const string& patronymic, size_t age)
	: name(name)
	, surname(surname)
	, age(age)
{
	if (name.empty() || surname.empty())
	{
		throw invalid_argument("name and surname can't be empty\n");
	}

	if (!IsAgeCorrect(age))
	{
		throw out_of_range("age must be between 14 and 60\n");
	}

	if (!patronymic.empty())
	{
		CStudent::patronymic = patronymic;
	}

	cout << name << " " << surname << " " << patronymic << ", " << age << " years old. Added" << endl;
}

std::string CStudent::GetPatronymic() const
{
	return patronymic;
};

size_t CStudent::GetAge() const
{
	return age;
};

std::string CStudent::GetName() const
{
	return name;
};

std::string CStudent::GetSurname() const
{
	return surname;
};

bool CStudent::IsAgeCorrect(const size_t age) const
{
	if (age < MIN_AGE || age > MAX_AGE)
	{
		return false;
	}

	return true;
}

bool CStudent::Rename(const string& newName, const string& newSurname, const string& newPatronymic)
{

	if (boost::trim_copy(newName).empty() || boost::trim_copy(newSurname).empty())
	{
		throw invalid_argument("name and surname cannot be empty\n");
		return false;
	}
	name = boost::trim_copy(newName);
	surname = boost::trim_copy(newSurname);

	if (!boost::trim_copy(patronymic).empty())
	{
		CStudent::patronymic = boost::trim_copy(patronymic);
	}

	return true;
};

bool CStudent::SetAge(const size_t newAge)
{
	if (!IsAgeCorrect(newAge))
	{
		throw out_of_range("age must be between 14 and 60 years old\n");
		return false;
	}

	if (newAge < age)
	{
		throw domain_error("new age can not be less\n");
		return false;
	}

	age = newAge;
	return true;
};