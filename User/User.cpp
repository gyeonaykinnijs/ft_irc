#include "User.hpp"

User::User()
{
	this->nickname = "*";
	this->userName = "";
	this->passwd = "";
	this->fd = 0;
	this->auth = NORMAL;
	this->buffer = "";
	this->isRegistered = false;
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

void User::setChannel(Channel *channel)
{
	this->channel = channel;
}

void User::setAuth(const User::Auth auth)
{
	this->auth = auth;
}

void User::setIgnored(const bool ignore)
{
	this->ignored = ignore;
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

User::Auth User::getAuth() const
{
	return this->auth;
}


bool User::getIsRegistered() const
{
	return this->isRegistered;
}

Channel* User::getChannel()
{
	return this->channel;
}

bool User::getIgnored() const
{
	return this->ignored;
}


void User::appendBuffer(string buffer)
{
	this->buffer.append(buffer);
}

