#ifndef __ChannelManager_H__
#define __ChannelManager_H__

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
	size_t channelCnt;
	std::map<size_t, Channel *> channel_list;
};

#endif