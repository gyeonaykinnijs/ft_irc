#include "UserManager.hpp"

UserManager::UserManager()
{}
UserManager::~UserManager()
{}


User* UserManager::getUser(std::string userName)
{
	return userList.at(userName);
}

void UserManager::setUser(User user)
{
	userList.insert(std::pair<std::string, User>(user.getNickName(), user));
}
