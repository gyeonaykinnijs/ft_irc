#ifndef __USERMANAGER_HPP__
#define __USERMANAGER_HPP__

#include "../defines.hpp"
#include "./User.hpp"

class UserManager
{
public:
	UserManager();
	~UserManager();
	/*
		Getter
	*/
	User* getUserByNickname(string nickname);
	User* getUserByFd(int fd);
	map<int, User *>& getAllUser();

	/*
		UserManager에서 User 등록
	*/

	void makeUser(int fd);
	void addUser(User *user);
	void addUserNickName(User *user);

	/*
		fd값으로 User 삭제
	*/
	void deleteUser(int fd);

private:
	map<string, User *> userListByNickname;
	map<int, User *> userListByFd;
};

#endif