#ifndef __CHANNELMANAGER_HPP__
#define __CHANNELMANAGER_HPP__

#include "defines.hpp"

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