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

	/**
	 * @brief Error Message 출력
	 * 
	 * 
	 * 		prefix 일단 지우고 나중에 필요하면 작성하기
	 */

	static string makeMessage(string code, string target, string message, string extra = "");


private:
	map<string, User *> userListByNickname;
	map<int, User *> userListByFd;
};

#endif