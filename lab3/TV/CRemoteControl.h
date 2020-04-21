#pragma once
#include <iostream>
#include <map>
#include <functional>
#include <iterator>
#include <sstream>
#include <string>
#include <algorithm>

class CTV;

class CRemoteControl
{
public:
	CRemoteControl(CTV& tv, std::istream& input);
	bool CommandHandler() const; 

private:
	bool TurnOn(std::istream& stream) const;
	bool TurnOff(std::istream& stream) const;
	bool Info(std::istream& stream) const;
	bool SelectChannel(std::istream& args) const;
	bool SelectPreviousChannel(std::istream& stream) const;
	bool SetChannelName(std::istream& stream) const;
	bool GetChannelName(std::istream& stream) const;
	bool GetChannelByName(std::istream& stream) const;
	bool DeleteChannel(std::istream& stream) const;

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::pair<std::string, std::string>, Handler>;

	CTV &m_tv;
	std::istream &m_input;
	ActionMap m_actions;
};