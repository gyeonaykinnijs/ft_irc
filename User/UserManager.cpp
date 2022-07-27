#include "UserManager.hpp"

UserManager::UserManager()
{}
UserManager::~UserManager()
{}


User* UserManager::getUserByNickname(string nickname)
{
	return this->userList.at(nickname);
}

User* UserManager::getUserByFd(int fd)
{
	return this->findFdUserList.at(fd);
}

std::map<int, User *> UserManager::getAllUser()
{
	return this->findFdUserList;
}

void UserManager::setUser(User user)
{
	this->userList.insert(pair<std::string, User>(user.getNickname(), user));
	this->findFdUserList.insert(pair<int, User>(user.getFd(), user));
}