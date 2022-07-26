#include "UserManager.hpp"

UserManager::UserManager()
{}
UserManager::~UserManager()
{}


User* UserManager::getUser(std::string userNickName)
{
	return userList.at(userNickName);
}

User* UserManager::getFdUser(int fd)
{
	return findFdUserList.at(fd);
}

void UserManager::setfdUser(User user)
{
	findFdUserList.insert(std::pair<int, User>(user.getFd(), user));
}

void UserManager::setUser(User user)
{
	userList.insert(std::pair<std::string, User>(user.getNickName(), user));
}