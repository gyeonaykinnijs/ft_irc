#ifndef __USERMANAGER_HPP__
#define __USERMANAGER_HPP__

#include "../defines.hpp"
#include "./User.hpp"

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

	
	void deleteUser(int fd);

private:
	map<string, User *> userListByNickname;
	map<int, User *> userListByFd;
};

#endif