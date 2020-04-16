#include "CTV.h"

using namespace std;

bool CTV::IsTurnedOn() const
{
	return isTvOn;
}

void CTV::TurnOn()
{
	if (IsTurnedOn())
	{
		cout << "!TV already ON\n";
		return;
	}

	size_t channel = 1;
	if (previousChannel != 0)
	{
		channel = previousChannel;
	}

	isTvOn = true;
	cout << "TV turned on, ";
	SelectChannel(channel);
}

void CTV::TurnOff()
{
	if (!IsTurnedOn())
	{
		cout << "!TV already OFF\n";
		return;
	}

	isTvOn = false;
	previousChannel = currentChannel;
	currentChannel = 0;
	cout << "TV turn off\n";
}

bool CTV::SelectChannel(size_t newChannel)
{
	if (!IsTurnedOn())
	{
		cout << "!Cant select channel, cuz TV is off\n";
		return false;
	}

	if ((newChannel < MIN_CHANNEL) || (newChannel > MAX_CHANNEL))
	{
		cout << "!Channel should be in range 0..99\n";
		return false;
	}

	previousChannel = currentChannel;
	currentChannel = newChannel;
	cout << "Channel is " << currentChannel << endl;
	return true;
}

void CTV::SelectChannel(string channelName)
{
	if (!IsTurnedOn())
	{
		cout << "!Cant select channel, cuz TV is off\n";
		return;
	}

	auto channelNum = GetChannelByName(channelName);
	if (channelNum)
	{
		previousChannel = currentChannel;
		currentChannel = channelNum.value();
		cout << "Switched on " << currentChannel << " - " << channelName << endl;
	}
	else
	{
		cout << "channel \"" << channelName << " \" doesnt exist \n";
	}
}

size_t CTV::GetCurrentChannel() const
{
	cout << "Current channel = " << currentChannel << endl;
	return currentChannel;
}

void CTV::SelectPreviousChannel()
{
	if (IsTurnedOn())
	{
		if (previousChannel != 0)
		{
			cout << "Switched on previous channel " << previousChannel << endl;
			currentChannel = previousChannel;
		}
		else
		{
			cout << "!You turn on TV for the first time, can't switch previous channel\n";
		}
	}
	else
	{
		cout << "!Cant switch on previous channel, cuz TV is off\n";
	}
}

bool CTV::SetChannelName(size_t channelNum, string channelName)
{
	if ((channelNum < MIN_CHANNEL) || (channelNum > MAX_CHANNEL))
	{
		cout << "!Channel should be in range 0..99\n";
		return false;
	}

	if (!IsTurnedOn())
	{
		cout << "!Cant select channel, cuz TV is off\n";
		return false;
	}

	auto name = GetChannelName(channelNum);
	if (name)
	{
		List::right_iterator itRight = channelList.right.find(name.value());
		channelList.right.replace_key(itRight, channelName);
		cout << channelNum << " was rename to " << channelName << endl;
		return true;
	}

	auto num = GetChannelByName(channelName);
	if (num)
	{
		List::left_iterator itLeft = channelList.left.find(num.value());
		channelList.left.replace_key(itLeft, channelNum);
		cout << channelName << " now its " << channelNum << endl;
		return true;
	}

	channelList.insert(List::value_type(channelNum, channelName));
	cout << channelName << " - " << channelNum << " added. \n";
	return true;
}

void CTV::Info() const
{
	if (IsTurnedOn())
	{
		cout << "Current channel is " << currentChannel << endl;
	}
	else
	{
		cout << "TV is off\n";
	}

	for (List::const_iterator iter = channelList.begin(), iend = channelList.end();
		 iter != iend; ++iter)
	{
		std::cout << iter->left << " - " << iter->right << std::endl;
	}
}

void CTV::DeleteChannel(string channelName)
{
	cout << channelName << " was deleted from Channel List\n";
	channelList.right.erase(channelName);
}

boost::optional<size_t> CTV::GetChannelByName(const string channelName)
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
