#pragma once

#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <boost/bimap.hpp>
#include <boost/optional.hpp>

typedef boost::bimap<size_t, std::string> List;

class CTV
{
public:
	bool IsOn() const;
	void TurnOn();
	void TurnOff();
	void Info() const;
	bool SelectChannel(size_t channel);
	void SelectChannel(std::string channelName);
	void SelectPreviousChannel();
	size_t GetCurrentChannel() const;
	bool SetChannelName(size_t channelNum, std::string channelName);
	void DeleteChannel(std::string channelName);
	boost::optional<std::string> GetChannelName(size_t channelNum);
	boost::optional<size_t> GetChannelByName(std::string channelName);

private:
	static constexpr size_t MIN_CHANNEL = 0;
	static constexpr size_t MAX_CHANNEL = 99;
	bool isTvOn = false;
	size_t currentChannel = 0;
	size_t previousChannel = 0;
	List channelList;

	
};
