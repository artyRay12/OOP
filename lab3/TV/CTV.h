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
	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();
	std::pair<size_t, List> Info() const;
	bool SelectChannel(size_t channel);
	bool SelectChannel(const std::string& channelName);
	bool SelectPreviousChannel();
	size_t GetCurrentChannel() const;
	bool SetChannelName(size_t channelNum, const std::string& channelName);
	bool DeleteChannel(const std::string& channelName);
	boost::optional<std::string> GetChannelName(size_t channelNum); //с const ругается на boost::bimap
	boost::optional<size_t> GetChannelByName(const std::string& channelName); //с const ругается на boost::bimap

private:
	static constexpr size_t MIN_CHANNEL = 0;
	static constexpr size_t MAX_CHANNEL = 99;
	bool isTvOn = false;
	size_t currentChannel = 0;
	size_t previousChannel = 0;
	List channelList;

	
};
