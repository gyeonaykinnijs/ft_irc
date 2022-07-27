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
	Channel getChannel(size_t channelId);
	void addChannel();
	void deleteChannel(size_t channelId);

private:
	map<string, Channel *> channel_list;
};

#endif