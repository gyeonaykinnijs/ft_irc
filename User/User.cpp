#include "User.hpp"

User::User()
{
	this->nickName = "deafult";
	this->userName = "default";
	this->userId = 0;
	this->participateChannelId = 0;
	this->fd = 0;
}
User::User(const std::string nickname, const std::string userName) : nickName(nickName), userName(userName)
{

}

User::~User()
{}

void User::setNickName(const std::string nickName)
{
	this->nickName = nickName;
}

void User::setUserName(const std::string userName)
{
	this->userName = userName;
}
void User::setUserId(const size_t userId)
{
	this->userId = userId;
}

void User::setFd(const int fd)
{
	this->fd = fd;
}

std::string User::getnickname()
{
	return this->nickName;
}

std::string User::getUserName()
{
	return this->userName;
}

size_t User::getUserId()
{
	return this->userId;
}

int User::getFd()
{
	return this->fd;
}