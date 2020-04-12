#pragma once
#include <iostream>
#include <map>
#include <cctype>
#include <functional>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

class CTV;
class CRemoteControl;
using function_t = void(*)();

typedef std::map<std::string, std::function<void(std::istream& stream)>> Actions;

class CRemoteControl
{
public:
	CRemoteControl(CTV& tv);
	//~CRemoteControl();
	//bool HandleCommand();

	//private:
	void TurnOn(std::istream& stream);
	void TurnOff(std::istream& stream);
	void Info(std::istream& stream);
	void SelectChannel(std::istream& args);
	void SelectPreviousChannel(std::istream& stream);
	void CommandHandler();
	void SetChannelName(std::istream& stream);
	//void SaveChannel();
	//void WhatChannelNumber();
	//bool WhatChannelName();

	CTV& m_tv;
	Actions m_actions;
};