#include "CTV.h"

using namespace std;

bool CTV::IsTurnedOn() const
{
	return isTvOn;
}

void CTV::TurnOn()
{
	size_t channel = 1;
	if (previousChannel != 0)
	{
		channel = previousChannel;
	}

	isTvOn = true;
	SelectChannel(channel);
}

void CTV::TurnOff()
{
	if (!IsTurnedOn())
	{
		return;
	}

	isTvOn = false;
	previousChannel = currentChannel;
	currentChannel = 0;
}

bool CTV::SelectChannel(size_t newChannel)
{

	if ((newChannel < MIN_CHANNEL) || (newChannel > MAX_CHANNEL))
	{
		return false;
	}

	previousChannel = currentChannel;
	currentChannel = newChannel;
	return true;
}

bool CTV::SelectChannel(const string& channelName)
{

	auto channelNum = GetChannelByName(channelName);
	if (channelNum)
	{
		previousChannel = currentChannel;
		currentChannel = channelNum.value();
		return true;
	}
	else
	{
		return false;
	}
}

size_t CTV::GetCurrentChannel() const
{
	return currentChannel;
}

bool CTV::SelectPreviousChannel()
{
		if (previousChannel != 0)
		{
			currentChannel = previousChannel;
			return true;
		}
		else
		{
			return false;
		}
}

bool CTV::SetChannelName(size_t channelNum, const string& channelName)
{
	if ((channelNum < MIN_CHANNEL) || (channelNum > MAX_CHANNEL))
	{
		return false;
	}

	auto name = GetChannelName(channelNum);
	if (name)
	{
		List::right_iterator itRight = channelList.right.find(name.value());
		channelList.right.replace_key(itRight, channelName);
		return true;
	}

	auto num = GetChannelByName(channelName);
	if (num)
	{
		List::left_iterator itLeft = channelList.left.find(num.value());
		channelList.left.replace_key(itLeft, channelNum);
		return true;
	}

	channelList.insert(List::value_type(channelNum, channelName));
	return true;
}

pair<size_t, List> CTV::Info() const
{
	return make_pair(currentChannel, channelList);
}

bool CTV::DeleteChannel(const string& channelName)
{
	List::right_iterator itRight = channelList.right.find(channelName);
	if (itRight != channelList.right.end())
	{
		channelList.right.erase(channelName);
		return true;
	}

	return false;
}

boost::optional<size_t> CTV::GetChannelByName(const string& channelName)
{
	List::right_iterator itRight = channelList.right.find(channelName);
	if (itRight != channelList.right.end())
	{
		return itRight->second;
	}

	return boost::none;
}

boost::optional<string> CTV::GetChannelName(size_t channelNum)
{
	List::left_iterator itLeft = channelList.left.find(channelNum);
	if (itLeft != channelList.left.end())
	{
		return itLeft->second;
	}

	return boost::none;
}
