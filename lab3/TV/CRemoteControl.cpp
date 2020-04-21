#include "CRemoteControl.h"
#include "CTV.h"
#include "boost/algorithm/string.hpp"
#include <boost/optional.hpp> //bimap не работал с 17-ым стандартом, поэтому optional от boost
#include <iterator>

using namespace std;
using namespace boost::algorithm;

CRemoteControl::CRemoteControl(CTV& tv, istream& input)
	: m_tv(tv)
	, m_input(input)
	, m_actions({
		  { make_pair("TurnOn", "On"), [this](istream& stream) { return TurnOn(stream); } },
		  { make_pair("TurnOff", "Off"), bind(&CRemoteControl::TurnOff, this, placeholders::_1) },
		  { make_pair("SelectChannel", "SC"), bind(&CRemoteControl::SelectChannel, this, placeholders::_1) },
		  { make_pair("SelectPreviousChannel", "SPC"), bind(&CRemoteControl::SelectPreviousChannel, this, placeholders::_1) },
		  { make_pair("SetChannelName", "SCN"), bind(&CRemoteControl::SetChannelName, this, placeholders::_1) },
		  { make_pair("GetChannelName", "GCN"), bind(&CRemoteControl::GetChannelName, this, placeholders::_1) },
		  { make_pair("GetChannelByName", "GCBN"), bind(&CRemoteControl::GetChannelByName, this, placeholders::_1) },
		  { make_pair("DeleteChannel", "DC"), bind(&CRemoteControl::DeleteChannel, this, placeholders::_1) },
		  { make_pair("Info", "?"), bind(&CRemoteControl::Info, this, placeholders::_1) },
	  })

{
	cout << "The remote was connected to TV \n\n";
}

bool CRemoteControl::CommandHandler() const
{
	string command;
	getline(m_input, command);

	stringstream commandStream(command);
	string action;

	commandStream >> action;

	auto it = m_actions.begin();
	for (it; it != m_actions.end(); it++)
	{
		if ((it->first.first == action) || (it->first.second == action))
		{
			break;
		}
	}

	if (it != m_actions.end())
	{

		return it->second(commandStream);
	}
	else
	{
		cout << "!! Invalid command\n";
		return false;
	}

	return true;
}

bool CRemoteControl::GetChannelName(istream& stream) const
{
	size_t channelNum;
	stream >> channelNum;

	auto channelName = m_tv.GetChannelName(channelNum);
	if (channelName)
	{
		cout << channelNum << " is " << channelName.value() << endl;
	}
	else
	{
		cout << "Channel " << channelNum << " doesn't have a name" << endl;
		return false;
	}

	return true;
}

bool CRemoteControl::GetChannelByName(istream& stream) const
{
	string channelName;
	stream >> channelName;
	m_tv.GetChannelByName(channelName);

	auto channelNum = m_tv.GetChannelByName(channelName);
	if (channelNum)
	{
		cout << channelNum.value() << " is " << channelName << endl;
	}
	else
	{
		cout << "Channel " << channelName << " doesn't exist" << endl;
		return false;
	}

	return true;
}

bool CRemoteControl::DeleteChannel(istream& stream) const
{
	string channelName;
	string partOfChannelName;

	while (getline(stream, partOfChannelName, ' '))
		if (!partOfChannelName.empty())
			channelName += partOfChannelName + ' ';

	if (channelName.empty())
	{
		cout << "!! If u want set channel use \"DeleteChannel <channel name>\"\n";
		return false;
	}

	bool isChannelDeleted = m_tv.DeleteChannel(trim_copy(channelName));
	if (!isChannelDeleted)
	{
		cout << channelName << " doesn't exist\n";
		return false;
	}

	cout << channelName << " was deleted from Channel List\n";
	return true;
}

bool CRemoteControl::SetChannelName(istream& stream) const
{
	string channelNum;
	size_t channelNumber;
	stream >> channelNum;

	if (!m_tv.IsTurnedOn())
	{
		cout << "!Cant set channel, cuz TV is off\n";
		return false;
	}

	if (channelNum.empty())
	{
		cout << "!! If u want set channel use \"SetChannelName <number> <channel name>\"\n";
		return false;
	}

	try
	{
		channelNumber = stoi(channelNum);
	}
	catch (exception e)
	{
		cout << "!! If u want set channel use \"SetChannelName <number> <channel name>\"\n";
		return false;
	}

	string channelName;
	string partOfChannelName;

	while (getline(stream, partOfChannelName, ' '))
		if (!partOfChannelName.empty())
			channelName += partOfChannelName + ' ';

	if (channelName.empty())
	{
		cout << "!! If u want set channel use \"SetChannelName <number> <channel name>\"\n";
		return false;
	}

	bool isChannelSet = m_tv.SetChannelName(static_cast<size_t>(channelNumber), trim_copy(channelName));
	if (!isChannelSet)
	{
		cout << "Channel should be in range 01..99\n";
	}
	cout << "Now \"" << channelNumber << "\" set as " << channelName << endl;

	return true;
}

bool CRemoteControl::TurnOn(istream& stream) const
{
	if (m_tv.IsTurnedOn())
	{
		cout << "TV already on\n";
		return false;
	}

	m_tv.TurnOn();
	cout << "TV turned on\n";
	stream.clear();
	return true;
}

bool CRemoteControl::TurnOff(istream& stream) const
{
	if (!m_tv.IsTurnedOn())
	{
		cout << "TV already off\n";
		return false;
	}

	m_tv.TurnOff();
	cout << "TV turned off, ";
	stream.clear();
	return true;
}

bool CRemoteControl::SelectChannel(std::istream& args) const
{
	string newChannelName;
	size_t newChannelNum;
	args >> newChannelName;

	if (!m_tv.IsTurnedOn())
	{
		cout << "!Cant select channel, cuz TV is off\n";
		return false;
	}
	if (newChannelName.empty())
	{
		cout << "!! If u want select channel use, SC <new channel name or number>\n";
		return false;
	}

	try
	{
		newChannelNum = stoi(newChannelName);

		bool isChannelSelected = m_tv.SelectChannel(newChannelNum);
		if (!isChannelSelected)
		{
			cout << "Channel should be 01..99\n";
			return false;
		}
		cout << "Switched on " << newChannelNum << endl;
	}
	catch (exception e)
	{
		bool isChannelSelected = m_tv.SelectChannel(newChannelName);
		if (!isChannelSelected)
		{
			cout << "channel \"" << newChannelName << " \" doesnt exist \n";
			return false;
		}
		cout << "Switched on " << newChannelName << endl;
	}

	return true;
}

bool CRemoteControl::SelectPreviousChannel(istream& stream) const
{
	if (!m_tv.IsTurnedOn())
	{
		cout << "!Cant select channel, cuz TV is off\n";
		return false;
	}

	bool isChannelSelected = m_tv.SelectPreviousChannel();
	if (!isChannelSelected)
	{
		cout << "!You turn on TV for the first time, can't switch previous channel\n";
		return false;
	}

	cout << "Switched on previous channel\n";
	stream.clear();
	return true;
}

bool CRemoteControl::Info(istream& stream) const
{
	stream.clear();

	if (!m_tv.IsTurnedOn())
	{
		cout << "TV is Off\n";
		return true;
	}

	auto info = m_tv.Info();

	cout << "TV is On\n";
	cout << "Current channel is " << info.first << endl;
	
	for (List::const_iterator iter = info.second.begin(), iend = info.second.end();
		 iter != iend; ++iter)
	{
		std::cout << iter->left << " - " << iter->right << std::endl;
	}

	return true;
}
