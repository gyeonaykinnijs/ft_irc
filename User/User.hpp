#ifndef __User_H__
#define __User_H__
#include <string>

class User{
public:
	User();
	~User();

	void setNickName(const std::string nickName);
	void setUserName(const std::string userName);
	void setUserFd(const std::string userFd);
	void getNickName();
	void getUserName();
	void getUserFd();


	std::string nickName;
	std::string userName;
	size_t		userFd;
	
};

#endif