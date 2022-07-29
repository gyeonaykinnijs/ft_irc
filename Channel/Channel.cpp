#include "Channel.hpp"

Channel::Channel()
{
	this->channelName = "deafult";
	this->maxSizeUser = 10;
	this->curSizeUser = 0;
}

Channel::~Channel()
{}

void Channel::setChannelName(const std::string channelName)	
{
	this->channelName = channelName;
}


void Channel::setCurSizeUser(const int size)
{
	this->curSizeUser = size;
}

string Channel::getChannelName() const
{
	return this->channelName;
}

int Channel::getCurSizeUser() const
{
	return this->curSizeUser;
}

int Channel::getMaxSizeUser() const
{
	return this->maxSizeUser;
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
