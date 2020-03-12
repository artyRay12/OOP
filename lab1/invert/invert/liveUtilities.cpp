optional<vector<char>> parseLine(const string& line)
{
	vector<char> genLine;
	for (auto& elem : line)
	{
		cout << elem;
		if (chars.find(elem) == chars.end())
		{
			cout << "wrong char DETECTED!!!";
			return nullopt;
		}
		genLine.push_back(elem);
	}
	return genLine;
}

optional<vector<vector<char>>> getFirstGeneration(istream& input)
{
	vector<vector<char>> firstGeneration;
	string line;
	int lineLength = 0;

	while (getline(input, line))
	{
		if (line.size() != lineLength)
		{
			cout << "MAP error, all lines should be same length";
		}

		auto generationLine = parseLine(line);
		if (!generationLine)
		{
			return nullopt;
		}

		firstGeneration.push_back(generationLine.value());
		cout << endl;
	}

	return firstGeneration;
}

optional<vector<vector<char>>> getFirstGenerationFromFile(const string& inputFileName)
{
	ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		cout << "Can't open file: " << inputFileName << endl;
		return nullopt;
	}

	return getFirstGeneration(input);
}




optional<vector<vector<char>>> live(const string& inputFileName, const string& outputFileName)
{
	auto firstGeneration = getFirstGenerationFromFile(inputFileName);


	return nullopt;

}