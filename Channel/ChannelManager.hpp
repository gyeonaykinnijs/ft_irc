#ifndef __ChannelManager_H__
#define __ChannelManager_H__

#include "Channel.hpp"
#include <vector>

class ChannelManager{
	
	public:
		std::vector<Channel *> channel_list;
	
	ChannelManager();
	~ChannelManager();
	void getChannel();
	void addChannel();
	void deleteChannel();
};

#endif