#include "CRemoteControl.h"
#include "CTV.h"
#include "boost/algorithm/string.hpp"

using namespace std;
using namespace boost::algorithm;

CRemoteControl::CRemoteControl(CTV& tv)
	: m_tv(tv)
	, m_actions({
		  { "On", [&](istream& stream) { return TurnOn(stream); } },
		  { "Off", [&](istream& stream) { return TurnOff(stream); } },
		  { "SC", [&](istream& stream) { return SelectChannel(stream); } },
		  { "SPC", [&](istream& stream) { return SelectPreviousChannel(stream); } },
		  { "Info", [&](istream& stream) { return Info(stream); } },

	  })

{
	cout << "The remote was connected to the TV \n\n";
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

		if (auto it = m_actions.find(action); it != m_actions.end()) // чтобы работал такой if надо включить в проекте поддержку C++17
		{
			it->second(commandStream);
		}
		else
		{
			cout << "Invalid command\n";
		}
	}
}
