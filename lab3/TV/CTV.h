#pragma once

#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <boost/bimap.hpp>

typedef boost::bimap<size_t, std::string> List;

class CTV
{
public:
	bool IsOn() const;
	void TurnOn();
	void TurnOff();
	void Info() const;
	void SelectChannel(size_t channel);
	void SelectPreviousChannel();
	size_t GetCurrentChannel() const;
	void SetChannelName(size_t channelNum, std::string channelName);

private:
	static constexpr size_t MIN_CHANNEL = 0;
	static constexpr size_t MAX_CHANNEL = 99;
	bool isTvOn = false;
	size_t currentChannel = 0;
	size_t previousChannel = 0;

	List channelList;

	
};
