#include "lab3/TV/CRemoteControl.h"
#include "lab3/TV/CTV.h"
#include <catch2/catch.hpp>

using namespace std;


stringstream input;
void SetInput(string str1, stringstream& stream = input)
{
	stream.clear();
	stream << str1;
}

TEST_CASE("Check RemoteControl() that connected and check that CommandHandler() can get main commands")
{
	CTV tv;
	CRemoteControl rc(tv, input);

	SECTION("Check RemoteControl(), TurnOn and TurnOff functions")
	{
		SetInput("On");
		rc.CommandHandler();
		REQUIRE(tv.IsTurnedOn());

		SetInput("Off");
		rc.CommandHandler();
		REQUIRE(!tv.IsTurnedOn());
	}
}

TEST_CASE("Check all comnands for CommandHandler()")
{

	CTV tv;
	CRemoteControl rc(tv, input);

	WHEN("TV is on")
	{
		SetInput("On");
		rc.CommandHandler();

		GIVEN("unknown command")
		{
			SetInput("ImNotExistAsCommand");
			CHECK(!rc.CommandHandler());
		}

		SECTION("check 'SelectChannel() <newChannelNum>' or 'SC()' should change currentChannel")
		{
			GIVEN("number as channel")
			{
				WHEN("number out of 0..99 range, currentChannel shouldn't change")
				{
					size_t oldChannel = tv.GetCurrentChannel();

					string newChannel = "999";
					SetInput("SelectChannel " + newChannel);
					rc.CommandHandler();

					CHECK(tv.GetCurrentChannel() == oldChannel);
				}

				WHEN("no args")
				{
					SetInput("SelectChannel");
					CHECK(!rc.CommandHandler());
				}

				WHEN("number in 0..99 range, currentChannel will change")
				{
					string newChannel = "12";
					SetInput("SelectChannel " + newChannel);
					rc.CommandHandler();

					CHECK(tv.GetCurrentChannel() == stoi(newChannel));
				}
			}
		}

		SECTION("check SelectPreviousChannel() or 'SPC', it should select previous channel obviously")
		{
			WHEN("after turnOn we didnt select any channel, and try to select on prevoius channel, current channel will be same")
			{
				size_t beforeSPC = tv.GetCurrentChannel();

				SetInput("SelectPreviousChannel");
				rc.CommandHandler();

				CHECK(beforeSPC == tv.GetCurrentChannel());
			}

			WHEN("after some 'SelectChannel()', 'SelectPreviousChannel()' should change channel to prevoius")
			{
				SetInput("SelectChannel 12");
				rc.CommandHandler();

				SetInput("SelectChannel 84");
				rc.CommandHandler();

				SetInput("SelectPreviousChannel");
				rc.CommandHandler();

				CHECK(tv.GetCurrentChannel() == 12);
			}

			WHEN("TurnOn TV not the first time, channel should switch on last before TurnOff")
			{
				SetInput("SelectChannel 12");
				rc.CommandHandler();

				SetInput("Off");
				rc.CommandHandler();
				SetInput("On");
				rc.CommandHandler();

				CHECK(tv.GetCurrentChannel() == 12);
			}
		}

		SECTION(" 'SetChannelName() or 'SCN <channelNum> <channelName>' should pin channelName to channelNum")
		{

			WHEN("args is fine")
			{
				string channelName = "BBC";
				string channelNumber = "12";
				SetInput("SetChannelName " + channelNumber + " " + channelName);
				rc.CommandHandler();

				INFO(" GetChannelByName() as GCBN <channelName> should return channelNumber by channelName");
				CHECK(tv.GetChannelByName(channelName).value() == stoi(channelNumber));

				INFO(" GetChannelName() as GCN <channelNumber> should return channelName by channelNumber");
				CHECK(tv.GetChannelName(stoi(channelNumber)).value() == channelName);
			}

			WHEN("wrong arguments => nothing to happen")
			{
				SetInput("SetChannelName stringInsteadNumber OPT");
				rc.CommandHandler();

				SetInput("SetChannelName 888 OPT");
				rc.CommandHandler();

				INFO(" GetChannelName() as GCN <channelNumber> should return none here");
				CHECK(!tv.GetChannelByName("OPT"));
			}

			WHEN("without args")
			{
				SetInput("SetChannelName OPT");
				CHECK(!rc.CommandHandler());

				SetInput("SetChannelName");
				CHECK(!rc.CommandHandler());
			}

			WHEN("ChannelNumber already pin to ChannelName")
			{
				string channel = "National Geographic";

				SetInput("SetChannelName 12 BBC");
				rc.CommandHandler();

				INFO("Add new channel with same number")
				SetInput("SetChannelName 12 " + channel);
				rc.CommandHandler();

				CHECK(tv.GetChannelName(12).value() == channel);
			}

			WHEN("ChannelName already pin to channelNum, ChannelName will be pin to new channelNum")
			{
				SetInput("SetChannelName 12 BBC");
				rc.CommandHandler();

				SetInput("SetChannelName 14 BBC");
				rc.CommandHandler();

				CHECK(tv.GetChannelByName("BBC").value() == 14);
			}

			WHEN("DeleteChannel as 'DC <channelName>' should delete channel by Name")
			{
				SetInput("SetChannelName 12 BBC");
				rc.CommandHandler();

				SetInput("DeleteChannel BBC");
				rc.CommandHandler();

				CHECK(!tv.GetChannelByName("BBC"));
				CHECK(!tv.GetChannelName(12));
			}
		}

		SECTION("We can SetChannelName(), lets go test SelectChannel() by string as 'SC <channelName>'")
		{
			SetInput("On"); 
			rc.CommandHandler();

			SetInput("SetChannelName 12 BBC");
			rc.CommandHandler();

			SetInput("SelectChannel 12");
			rc.CommandHandler();

			WHEN("channelName doestExist")
			{
				SetInput("SC neverMind");
				CHECK(tv.GetCurrentChannel() == 12);
			}

			WHEN("channelName exist")
			{
				SetInput("SetChannelName 5 neverMind");
				rc.CommandHandler();

				SetInput("SelectChannel neverMind");
				rc.CommandHandler();

				CHECK(tv.GetCurrentChannel() == 5);
			}
		}
	}
}
