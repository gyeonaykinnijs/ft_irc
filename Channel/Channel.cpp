#include "Channel.hpp"

Channel::Channel()
{
	this->channelName = "deafult";
}

Channel::~Channel()
{}

void Channel::setChannelName(const std::string ChannelName)	
{
	this->channelName = channelName;
}
std::string Channel::getChannelName()
{
	return this->channelName;
}