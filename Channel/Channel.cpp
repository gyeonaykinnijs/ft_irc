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

void Channel::setChannelId(size_t channelId)
{
	this->channelId = channelId;
}

std::string Channel::getChannelName()
{
	return this->channelName;
}

size_t Channel::getChannelId()
{
	return this->channelId;
}

void Channel::addJoinUser(User user)
{
		joinUser.insert(pair<std::string, User>(user.getNickName(), user));
}

void Channel::deleteJoinUser(User user)
{
	joinUser.eraser(user.getUserName());
}

std::vector<User *> Channel::getJoinUser()
{
	std::vector<User *> userList;


	auto iter = joinUser.begin();
    while (iter != joinUser.end()) {
		userList.push_back(iter->second);
        ++iter;
    }

	return userList;
}
