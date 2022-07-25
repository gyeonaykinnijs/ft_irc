#include "ChannelManager.hpp"

ChannelManager::ChannelManager()
{
	this->channelCnt = 0;
}

ChannelManager::~ChannelManager()
{}

Channel ChannelManager::getChannel(size_t channelId)
{
	return channel_list.find(channelId);
}

void ChannelManager::addChannel()
{
	this->channelCnt++;
	Channel *channel = new Channel;
	channel_list.insert(std::pair<size_t, Channel>(channelCnt, channel));
}

void ChannelManager::deleteChannel(size_t channelId)
{
	channel_list.erase(channelId);
}