#ifndef __CHANNELMANAGER_H__
#define __CHANNELMANAGER_H__

#include "Channel.hpp"
#include <map>
using namespace std;

class ChannelManager
{
public:
	ChannelManager();
	~ChannelManager();
	Channel* getChannel(string channelName);
	Channel *createChannel(string channelName, string passwd, User *user);
	void deleteChannel(string channelName);

private:
	map<string, Channel *> channel_list;

};

#endif