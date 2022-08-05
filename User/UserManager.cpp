#include "UserManager.hpp"

UserManager::UserManager()
{}

UserManager::~UserManager()
{}

User* UserManager::getUserByNickname(string nickname)
{
	return this->getUserByFd(this->userFdByName[nickname]);
}

User* UserManager::getUserByFd(int fd)
{
	return this->userListByFd[fd];
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
	this->userListByFd.insert(make_pair(user->getFd(), user));
	this->userFdByName.insert(pair<string, int>(user->getUserName(), user->getFd()));
}

void UserManager::makeUser(int fd)
{
	User *user = new User;
	user->setFd(fd);
	addUser(user);
}

void UserManager::deleteUser(int fd)
{
	map<string, Channel *> channel = this->userListByFd[fd]->getChannelList();
	this->userFdByName.erase(getUserByFd(fd)->getUserName());
	this->userListByFd.erase(fd);
}

string UserManager::makeMessage(string code, string target, string message)
{
	string buffer;

	buffer = code + (code.size() ? " " : "") + target + " : " + message + "\r\n";
	return buffer;
}

bool UserManager::hasNickname(const string nickname)
{
	for(map<int, User *>::iterator iter = userListByFd.begin(); iter != userListByFd.end(); iter++)
	{
		if (iter->second->getNickname() == nickname)
		{
			return true;
		}
	}
	return false;
}