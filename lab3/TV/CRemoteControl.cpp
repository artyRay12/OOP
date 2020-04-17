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

CRemoteControl::~CRemoteControl()
{
}

bool CRemoteControl::CommandHandler()
{
	string command;
	getline(m_input, command);

	stringstream commandStream(command);
	string action;

	commandStream >> action;

	auto it = m_actions.begin();
	for(it; it != m_actions.end(); it++)
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

bool CRemoteControl::DeleteChannel(istream& stream)
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

	m_tv.DeleteChannel(trim_copy(channelName));
	return true;
}

bool CRemoteControl::SetChannelName(istream& stream)
{
	string channelNum;
	size_t channelNumber;
	stream >> channelNum;

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

	m_tv.SetChannelName(static_cast<size_t>(channelNumber), trim_copy(channelName));
	return true;
}

bool CRemoteControl::TurnOn(istream& stream)
{
	m_tv.TurnOn();
	return true;
}

bool CRemoteControl::TurnOff(istream& stream)
{
	m_tv.TurnOff();
	return true;
}

bool CRemoteControl::SelectChannel(std::istream& args)
{
	string newChannelName;
	size_t newChannelNum;
	args >> newChannelName;

	if (newChannelName.empty())
	{
		cout << "!! If u want select channel use, SC <new channel name or number>\n";
		return false;
	}

	try
	{
		newChannelNum = stoi(newChannelName);
		m_tv.SelectChannel(newChannelNum);
	}
	catch (exception e)
	{
		m_tv.SelectChannel(newChannelName);
	}

	return true;
}

bool CRemoteControl::SelectPreviousChannel(istream& stream)
{
	m_tv.SelectPreviousChannel();
	return true;
}

bool CRemoteControl::Info(istream& stream) const
{
	m_tv.Info();
	return true;
}
