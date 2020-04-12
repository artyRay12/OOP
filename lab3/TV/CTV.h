#pragma once

#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

const size_t COMMAND = 0;
const size_t COMMAND_ARGUMENT_1 = 1;
const size_t COMMAND_ARGUMENT_2 = 2;

class CTV
{
public:
	bool IsOn() const;
	void TurnOn();
	void TurnOff();
	void Info() const;
	void SelectChannel(size_t channel);
	void SelectPreviousChannel();
	size_t GetCurrentChannel(std::istream& args) const;
	void CommandProcessor(std::string command);

private:
	static constexpr size_t MIN_CHANNEL = 0;
	static constexpr size_t MAX_CHANNEL = 99;
	bool isTvOn = false;
	size_t currentChannel = 0;
	size_t previousChannel = 0;
};
