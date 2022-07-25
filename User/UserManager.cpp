#include "UserManager.hpp"

UserManager::UserManager()
{}
UserManager::~UserManager()
{}


User* UserManager::getUser(User user)
{
	return userList.at(user.getNickName());
}

void UserManager::setUser(User user)
{
	userList.insert(std::pair<std::string, User>(user.getNickName(), user));
}
