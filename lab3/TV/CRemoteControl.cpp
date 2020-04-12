#include "CRemoteControl.h"
#include "CTV.h"
#include "boost/algorithm/string.hpp"
#include <iterator>

using namespace std;
using namespace boost::algorithm;

CRemoteControl::CRemoteControl(CTV& tv)
	: m_tv(tv)
	, m_actions({
		  { "On", [&](istream& stream) { return TurnOn(stream); } },
		  { "Off", [&](istream& stream) { return TurnOff(stream); } },
		  { "SC", [&](istream& stream) { return SelectChannel(stream); } },
		  { "SPC", [&](istream& stream) { return SelectPreviousChannel(stream); } },
		  { "SCN", [&](istream& stream) { return SetChannelName(stream); } },
		  { "Info", [&](istream& stream) { return Info(stream); } },
	  })

{
	cout << "The remote was connected to the TV \n\n";
}

void CRemoteControl::SetChannelName(istream& stream)
{
	size_t channelNum;
	stream >> channelNum;
	string channelName;
	string partOfChannelName;

	while (getline(stream, partOfChannelName,' '))
		if (!partOfChannelName.empty())
			channelName += partOfChannelName + ' ';


	m_tv.SetChannelName(channelNum, channelName);

}

void CRemoteControl::TurnOn(istream& stream)
{
	m_tv.TurnOn();
}

void CRemoteControl::TurnOff(istream& stream)
{
	m_tv.TurnOff();
}

void CRemoteControl::SelectChannel(std::istream& args)
{
	size_t newChannel;
	args >> newChannel;
	m_tv.SelectChannel(newChannel);
}

void CRemoteControl::SelectPreviousChannel(istream& stream)
{
	m_tv.SelectPreviousChannel();
}

void CRemoteControl::Info(istream& stream)
{
	m_tv.Info();
}

void CRemoteControl::CommandHandler()
{
	string command;
	while (getline(cin, command))
	{
		stringstream commandStream(command);
		string action;
		commandStream >> action;

		auto it = m_actions.find(action);
		if (it != m_actions.end())
		{
			it->second(commandStream);
		}
		else
		{
			cout << "Invalid command\n";
		}
	}
}
