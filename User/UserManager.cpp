#include "UserManager.hpp"

UserManager::UserManager()
{}

UserManager::~UserManager()
{}

User* UserManager::getUserByNickname(const string nickname)
{
	const  string nick = nickname;
	int fd = this->userFdByName[nick];
	return this->getUserByFd(fd);
}

User* UserManager::getUserByFd(int fd)
{
	if (this->userListByFd.count(fd) == 0)
	{
		return NULL;
	}
	return this->userListByFd[fd];
}

map<int, User *> &UserManager::getAllUser()
{
	return this->userListByFd;
}

void UserManager::addUser(User *user)
{
	this->userListByFd[user->getFd()] = user;
}

void UserManager::addUserFdByName(User *user)
{
	this->userFdByName[user->getNickname()] = user->getFd();
}

void UserManager::makeUser(int fd)
{
	User *user = new User;
	user->setFd(fd);
	addUser(user);
}

void UserManager::deleteUser(int fd)
{
	User *user = this->getUserByFd(fd);
	if (user != NULL)
	{
		this->userFdByName.erase(user->getNickname());
		this->userListByFd.erase(fd);
	}
}

string UserManager::makeMessage( string code, string target, string message)
{
	string buffer;
	string colon = message.size() == 0 ? "" : " :";

	buffer =  code + (code.size() ? " " : "") + target + colon + message + "\r\n";
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