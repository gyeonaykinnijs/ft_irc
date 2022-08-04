#include "UserManager.hpp"

UserManager::UserManager()
{}

UserManager::~UserManager()
{}

User* UserManager::getUserByNickname(string nickname)
{
	return this->getUserByFd(this->userNameByFd[nickname]);
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
	this->userListByFd.insert(pair<int, User *>(user->getFd(), user));
	this->userNameByFd.insert(pair<string, int>(user->getUserName(), user->getFd()));
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