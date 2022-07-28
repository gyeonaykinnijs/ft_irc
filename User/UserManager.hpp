#ifndef __USERMANAGER_HPP__
#define __USERMANAGER_HPP__

#include "User.hpp"
#include <vector>
#include <map>
#include <string>

using namespace std;


class UserManager
{
public:
	UserManager();
	~UserManager();
	User* getUserByNickname(string nickname);
	User* getUserByFd(int fd);
	map<int, User *>& getAllUser();
	void makeUser(int fd);
	void addUser(User *user);
	void addUserNickName(User *user);

private:
	map<string, User *> userListByNickname;
	map<int, User *> userListByFd;
};

#endif