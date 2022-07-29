#include "ChannelManager.hpp"

ChannelManager::ChannelManager()
{
}

ChannelManager::~ChannelManager()
{}

Channel* ChannelManager::getChannel(string channelName)
{
	return channel_list.at(channelName);
}

void ChannelManager::addChannel(string channelName)
{
	Channel *channel = new Channel;
	channel_list.insert(std::pair<string, Channel*>(channelName, channel));
}

void ChannelManager::deleteChannel(string channelName)
{
	channel_list.erase(channelName);
}