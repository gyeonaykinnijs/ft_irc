#ifndef __CHANNELMANAGER_H__
#define __CHANNELMANAGER_H__

#include "Channel.hpp"
#include <map>

class ChannelManager{
	
public:
	ChannelManager();
	~ChannelManager();
	Channel getChannel(size_t channelId);
	void addChannel();
	void deleteChannel(size_t channelId);

private:
	size_t channelCnt_;
	std::map<size_t, Channel *> channel_list_;
};

#endif