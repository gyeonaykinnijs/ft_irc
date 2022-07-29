#include "Channel.hpp"

Channel::Channel()
{
	this->channelName = "deafult";
}

Channel::~Channel()
{}

void Channel::setChannelName(const std::string channelName)	
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

void Channel::addJoinUser(User* user)
{
	joinUser.insert(make_pair(user->getNickname(), user));
}

void Channel::deleteJoinUser(User user)
{
	joinUser.erase(user.getUserName());
}

std::map<string, User *> Channel::getJoinUser()
{
	std::map<string, User *> userList;

	map<string, User *>::iterator iter = this->joinUser.begin();
    while (iter != joinUser.end()) {
		userList.insert(*iter);
        ++iter;
    }

	return userList;
}
