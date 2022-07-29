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
	/*
		user fd or nickname 중복 error error
	*/
	this->userListByFd.insert(pair<int, User *>(user->getFd(), user));
}

void UserManager::addUserNickName(User *user)
{
	/* 
		user fd or nickname 중복 error error
	*/
	this->userListByNickname.insert(pair<string, User *>(user->getUserName(), user));
}

void UserManager::makeUser(int fd)
{	
	/*
		user fd or nickname 중복 error error
	*/
	User *user = new User;
	user->setFd(fd);
	addUser(user);
}

void UserManager::deleteUser(int fd)
{
	User *user = userListByFd.at(fd);
	
	this->userListByNickname.erase(user->getUserName());
	this->userListByFd.erase(fd);

	delete user;
}