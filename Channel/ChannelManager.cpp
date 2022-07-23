#include "ChannelManager.hpp"

ChannelManager::ChannelManager()
{
	this->channelCnt = 0;
}

ChannelManager::~ChannelManager()
{}

Channel ChannelManager::getChannel(size_t channelFd)
{
	return map.at(channelFd);
}

void ChannelManager::addChannel()
{
	channelCnt++;
	Channel *channel = new Channel;
	channel_list.insert(pair<size_t, Channel>(channelCnt, channel));
}

void ChannelManager::deleteChannel(size_t channelFd)
{
	channel_list.erase(channelFd);
}