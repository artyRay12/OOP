#include "CTV.h"

using namespace std;

bool CTV::IsOn() const
{
	return isTvOn;
}

void CTV::TurnOn()
{
	isTvOn = true;
	cout << "-- TV turn on\n";
}

void CTV::TurnOff()
{
	isTvOn = false;
	currentChannel = 0;
	cout << "-- TV turn off\n";
}

void CTV::SelectChannel(size_t channel)
{
	if ((channel < MIN_CHANNEL) || (channel > MAX_CHANNEL))
	{
		cout << "Channel should be in range 0..99\n";
		return;
	}

	if (!IsOn())
	{
		cout << "Cant select channel, cuz TV is off\n";
		return;
	}

	previousChannel = currentChannel;
	currentChannel = channel;
	cout << "Switched on " << currentChannel << endl;
}

size_t CTV::GetCurrentChannel(istream& args) const
{
	cout << "Current channel = " << currentChannel << endl;
	return currentChannel;
}

void CTV::SelectPreviousChannel()
{
	if (IsOn())
	{
		cout << "Switched on previous channel " << previousChannel << endl;
		currentChannel = previousChannel;
	}
	else
	{
		cout << "Cant switch on previous channel, cuz TV is off\n";
	}
}

void CTV::CommandProcessor(string command)
{
}

void CTV::Info() const
{
	if (IsOn())
	{
		cout << "current channel is " << currentChannel << endl;
	}
	else
	{
		cout << "TV is off\n";
		cout << "current channel is 0\n";
	}
}
