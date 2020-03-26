#include "dictionary/dictionary.h"
#include "dictionary/fileUtilities.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

TEST_CASE("GetDictionary() take dictionary from stream and put it into map")
{

	string strFromDictionary = "dog - собака";
	stringstream stream(strFromDictionary);

	Dictionary dictionaryFromFile = GetDictionary(stream);

	Dictionary testDictionary;
	vector<string> translationWord;
	translationWord.push_back("собака");
	testDictionary.emplace("dog", translationWord);

	CHECK(dictionaryFromFile == testDictionary);
}

TEST_CASE("GetTranslate() get Dictionary and word for translate, and return translation")
{
	string word = "dog";
	string translatedWord = "собака";

	Dictionary testDictionary;
	vector<string> translationWord;
	translationWord.push_back("собака");
	testDictionary.emplace("dog", translationWord);

	CHECK(GetTranslate(testDictionary, word).value()[0] == translatedWord);
}
