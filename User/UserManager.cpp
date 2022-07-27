#include "UserManager.hpp"

UserManager::UserManager()
{}
UserManager::~UserManager()
{}


User* UserManager::getUserByNickname(string nickname)
{
	return this->userListByNickname.at(nickname);
}

User* UserManager::getUserByFd(int fd)
{
	return this->userListByFd.at(fd);
}

map<int, User *> &UserManager::getAllUser()
{
	return this->userListByFd;
}

void UserManager::addUser(User *user)
{
	this->userListByFd.insert(pair<int, User *>(user->getFd(), user));
}

void UserManager::addUserNickName(User *user)
{
	this->userListByNickname.insert(pair<string, User *>(user->getUserName(), user));
}

void UserManager::makeUser(int fd)
{	
	User *user = new User;
	user->setFd(fd);
	addUser(user);
}