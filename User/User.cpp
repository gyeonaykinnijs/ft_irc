#include "User.hpp"

User::User()
{
	this->nickname = "";
	this->userName = "";
	this->passwd = "";
	this->fd = 0;
}
User::User(const std::string nickname, const std::string userName) : nickname(nickname), userName(userName)
{

}

User::~User()
{}

void User::setNickname(const std::string nickname)
{
	this->nickname = nickname;
}

void User::setUserName(const std::string userName)
{
	this->userName = userName;
}
void User::setFd(const int fd)
{
	this->fd = fd;
}

void User::setBuffer(const string buffer)
{
	this->buffer = buffer;
}

void User::setIsRegistered(const bool isRegistered)
{
	this->isRegistered = isRegistered;
}

void User::setChannel(const channel *channel)
{
	this->channel = channel;
}


std::string User::getNickname() const
{
	return this->nickname;
}

std::string User::getUserName() const
{
	return this->userName;
}

int User::getFd() const
{
	return this->fd;
}

string User::getBuffer() const
{
	return this->buffer;
}

bool User::getIsRegistered() const
{
	return this->isRegistered;
}

Channel* User::getChannel() const
{
	return this->channel;
}