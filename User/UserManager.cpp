#include "UserManager.hpp"

UserManager::UserManager()
{}

UserManager::~UserManager()
{}

User* UserManager::getUserByNickname(const string nickname)
{
	cout << " == " << nickname << endl;
	const  string nick = nickname;
	int fd = this->userFdByName[nick];
	cout << " == fd == " << fd << endl;
	return this->getUserByFd(fd);
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
	this->userListByFd[user->getFd()] = user;
	// ***************** TODO: nickname 정하고 나서 맵에 넣어야 됨 **************** //
	this->userFdByName[user->getNickname()] = user->getFd();
	//cout << "userFdByName == " << this->userFdByName[user->getNickname()] << endl;
	// this->userListByFd.insert(make_pair(user->getFd(), user));
	// this->userFdByName.insert(pair<string, int>(user->getUserName(), user->getFd()));
}

void UserManager::makeUser(int fd)
{
	User *user = new User;
	user->setFd(fd);
	addUser(user);
}

void UserManager::deleteUser(int fd)
{
	this->userFdByName.erase(getUserByFd(fd)->getNickname());
	this->userListByFd.erase(fd);
}

string UserManager::makeMessage( string code, string target, string message)
{
	string buffer;
	string colon = message.size() == 0 ? "" : " : ";

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