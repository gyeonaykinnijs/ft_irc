#include "Channel.hpp"
#include "../User/User.hpp"

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

void Channel::setMakeUser(User *user)
{
	this->makeUser = user;
}

void Channel::setChannelKey(const string channelKey)
{
	this->channelKey = channelKey;
}

string Channel::getChannelName() const
{
	return this->channelName;
}

string Channel::getChannelKey() const
{
	return this->channelKey;
}

int Channel::getCurSizeUser() const
{
	return this->curSizeUser;
}

int Channel::getMaxSizeUser() const
{
	return this->maxSizeUser;
}

User* Channel::getMakeUser(const string nickname)
{
	return this->joinUser.at(nickname);
}

void Channel::insertJoinUser(User* user) 
{
	
	joinUser.insert(make_pair(user->getNickname(), user));
}

User* Channel::selectJoinUser(string userName)
{
	return joinUser.at(userName);
}

void Channel::deleteJoinUser(User *user) 
{
	joinUser.erase(user->getUserName());
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
