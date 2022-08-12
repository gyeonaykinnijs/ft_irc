#ifndef __USERMANAGER_HPP__
#define __USERMANAGER_HPP__

#include "../defines.hpp"
#include "./User.hpp"

class UserManager
{
public:
	UserManager();
	~UserManager();
	User* getUserByNickname(const string nickname);
	User* getUserByFd(int fd);
	map<int, User *>& getAllUser();
	void makeUser(int fd);
	void addUser(User *user);
	void addUserNickName(User *user);
	void deleteUser(int fd);
	static string makeMessage(string code, string target, string message);
	bool hasNickname(const string nickName); 

private:
	map<string, int> userFdByName;
	map<int, User *> userListByFd;
};

#endif
