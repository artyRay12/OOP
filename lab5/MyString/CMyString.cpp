#include "CMyString.h"
#include <iostream>
#include <exception>
using namespace std;

CMyString::CMyString()
	: CMyString("", 0)
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_value, other.m_length)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: CMyString(other.m_value, other.m_length)
{
	other.m_value = nullptr;
	other.m_length = 0;
}

CMyString::CMyString(string const& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
{
	try
	{
		m_value = new char[m_length + 1];
	}
	catch (const bad_alloc& e)
	{
		cout << e.what();
	}

	for (int i = 0; i < m_length; i++)
	{
		m_value[i] = pString[i];
	}

	m_value[m_length] = '\0';
}

CMyString::~CMyString()
{
	delete[] m_value;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if ((start > m_length) || (start + length > m_length))
	{
		throw std::out_of_range("Out of range");
	}

	if (length == SIZE_MAX)
	{
		return CMyString(m_value + start, m_length);
	}

	return CMyString(m_value + start, length);
}

const char* CMyString::GetStringData() const
{
	return m_value;
}

void CMyString::Clear()
{
	delete[] m_value;
	m_length = 0;
	m_value = new char[1];
	m_value[0] = '\0';
}

size_t CMyString::GetLength() const
{
	return m_length;
}

CMyString& const CMyString::operator=(const char* str2)
{
	if (m_value != nullptr)
	{
		delete[] m_value;
	}

	int length = strlen(str2);
	this->m_value = new char[length + 1];

	for (int i = 0; i < length; i++)
	{
		m_value[i] = str2[i];
	}
	m_value[length] = '\0';

	return *this;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (&other != this)
	{
		CMyString tmpCpy(other);
		swap(m_value, tmpCpy.m_value);
		swap(m_length, tmpCpy.m_length);
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (&other != this)
	{
		delete[] m_value;

		m_value = other.m_value;
		m_length = other.m_length;

		other.m_value = nullptr;
		other.m_length = 0;
	}

	return *this;
}

CMyString const operator+(const CMyString& str1, const CMyString& str2)
{
	size_t length = str1.GetLength() + str2.GetLength();
	char* value = new char[length];

	memcpy(value, str1.GetStringData(), str1.GetLength());
	memcpy(value + str1.GetLength(), str2.GetStringData(), str2.GetLength());

	CMyString myString = CMyString(value, length);
	delete[] value;

	return myString;
}

CMyString const operator+(const CMyString& str1, const string& str2)
{
	return CMyString(str1 + CMyString(str2));
}

CMyString const operator+(const CMyString& str1, const char* str2)
{
	return CMyString(str1 + CMyString(str2));
}

CMyString& CMyString::operator+=(const CMyString& str1)
{
	CMyString tmp = CMyString(*this + str1);

	swap(m_value, tmp.m_value);
	swap(m_length, tmp.m_length);

	return *this;
}

bool const operator==(const CMyString& str1, const CMyString& str2)
{
	if (str1.GetLength() != str2.GetLength())
		return false;

	size_t length = str1.GetLength() >= str2.GetLength() ? str1.GetLength() : str2.GetLength();
	for (size_t i = 0; i <= length; i++)
	{
		if (str1.GetStringData()[i] != str2.GetStringData()[i])
		{
			return false;
		}
	}

	return true;
}

bool const operator!=(const CMyString& str1, const CMyString& str2)
{
	return !(str1 == str2);
}

bool const operator<(const CMyString& str1, const CMyString& str2)
{
	if (str1 == str2)
	{
		return false;
	}

	for (size_t i = 0; i < str1.GetLength(), i < str2.GetLength(); i++)
	{

		if (str1.GetStringData()[i] < str2.GetStringData()[i])
		{
			return true;
		}

		if (str1.GetStringData()[i] > str2.GetStringData()[i])
		{
			return false;
		}
	}

	return str1.GetLength() < str2.GetLength() ? true : false;
}

bool const operator>(const CMyString& str1, const CMyString& str2)
{
	return str1 < str2 ? false : true;
}

bool const operator>=(const CMyString& str1, const CMyString& str2)
{
	return str1 == str2 ? true : str1 > str2 ? true : false;
}

bool const operator<=(const CMyString& str1, const CMyString& str2)
{
	return str1 == str2 ? true : str1 < str2 ? true : false;
}

const char& CMyString::operator[](size_t index) const
{
	try
	{
		if ((index > m_length) || (index < 0))
		{
			throw invalid_argument("cant get value by this index");
		}
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}

	return m_value[index];
}

char& CMyString::operator[](size_t index)
{
	try
	{
		if ((index > m_length) || (index < 0))
		{
			throw invalid_argument("cant get value by this index");
		}
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}

	return m_value[index];
}