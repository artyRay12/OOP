#include "censFilter/censor.h"
#include <catch2/catch.hpp>

using namespace std;

TEST_CASE("GetUncensoredWordsFromFile() take word from file and put them in set")
{
	SECTION("file exist")
	{
		string fileName = "badWordsTest.txt";
		set<string> badWords1{ "fuck", "bitch" };
		auto badWords = GetUncensoredWordsFromFile(fileName);
		CHECK(badWords.value() == badWords1);
	}

	SECTION("file not exist")
	{
		string notExistFileName = "imNotExist.txt";
		auto badWords = GetUncensoredWordsFromFile(notExistFileName);
		CHECK(nullopt == badWords);
	}
}

TEST_CASE("CensorString() should return new string where bad words replaced by ***")
{
	SECTION("not empty string")
	{
		string uncensString = "fuck+bitch1cat/dog.shit,shot";
		stringstream uncensStream(uncensString);
		set<string> badWords{ "fuck", "bitch", "shit" };

		string censString1 = "***+***1cat/dog.***,shot";

		string censStirng = String—ensor(uncensStream, badWords);
		CHECK(censString1 == censStirng);
	}

	SECTION("not empty string")
	{
		string uncensString = "";
		stringstream uncensStream(uncensString);
		set<string> badWords{ "fuck", "bitch", "shit" };

		string censString1 = "";

		string censStirng = String—ensor(uncensStream, badWords);
		CHECK(censString1 == censStirng);
	}
}