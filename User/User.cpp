#include "User.hpp"

User::User()
{
	this->nickName = "deafult";
	this->userName = "default";
	this->userFd = 0;
	this->participateChannelFd = 0;
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
void User::setUserFd(const size_t userFd)
{
	this->userFd = userFd;
}

std::string User::getNickName()
{
	return this->nickName;
}

std::string User::getUserName()
{
	return this->userName;
}

size_t User::getUserFd()
{
	return this->userFd;
}