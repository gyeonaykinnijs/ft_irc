#ifndef __CHANNELMANAGER_HPP__
#define __CHANNELMANAGER_HPP__

#include "../defines.hpp"
#include "./Channel.hpp"

class ChannelManager
{
	
public:
	ChannelManager();
	~ChannelManager();
	Channel* getChannel(string channelName);
	void addChannel(string channelName);
	void deleteChannel(string channelName);

private:
	map<string, Channel *> channel_list;
};

#endif