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

std::string User::getNickname()
{
	return this->nickname;
}

std::string User::getUserName()
{
	return this->userName;
}

int User::getFd()
{
	return this->fd;
}