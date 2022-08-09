#include "ChannelManager.hpp"

ChannelManager::ChannelManager()
{}

ChannelManager::~ChannelManager()
{}

Channel* ChannelManager::getChannel(const string channelName)
{
	if (this->channel_list.count(channelName) == 0)
		return NULL;
	return this->channel_list[channelName];
}

Channel* ChannelManager::createChannel(const string channelName, string passwd, User* user)
{
	Channel *channel = new Channel;
	channel->setChannelName(channelName);
	channel->setChannelKey(passwd);
	channel->setAdmin(user);
	channel->insertJoinUser(user);
	channel->setCurSizeUser(channel->getCurSizeUser() + 1);
	this->channel_list[channel->getChannelName()] =  channel;
	return channel;
}

void ChannelManager::deleteChannel(string channelName)
{
	channel_list.erase(channelName);
}