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

Channel* ChannelManager::createChannel(string channelName, string passwd, User* user)
{
	Channel *channel = new Channel;
	channel->setChannelName(channelName);
	channel->setChannelKey(passwd);
	channel->setMakeUser(user);
	channel->insertJoinUser(user);
	channel->setCurSizeUser(channel->getCurSizeUser() + 1);
	channel_list.insert(std::pair<string, Channel*>(channelName, channel));
	
	return channel;
}

void ChannelManager::deleteChannel(string channelName)
{
	channel_list.erase(channelName);
}