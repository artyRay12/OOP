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
	bool CommandHandler();
	~CRemoteControl();

private:
	bool TurnOn(std::istream& stream);
	bool TurnOff(std::istream& stream);
	bool Info(std::istream& stream) const;
	bool SelectChannel(std::istream& args);
	bool SelectPreviousChannel(std::istream& stream);
	bool SetChannelName(std::istream& stream);
	bool GetChannelName(std::istream& stream) const;
	bool GetChannelByName(std::istream& stream) const;
	bool DeleteChannel(std::istream& stream);

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::pair<std::string, std::string>, Handler>;

	CTV &m_tv;
	std::istream &m_input;
	ActionMap m_actions;
};