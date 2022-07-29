#ifndef __USER_HPP__
#define __USER_HPP__
#include "defines.hpp"

class User
{
public:
	User();
	User(const string nickname, const string userName);
	~User();

	void setNickname(const string nickName);
	void setUserName(const string userName);
	void setFd(const int fd);
	void setPasswd(const string passwd);
	void setBuffer(const string buffer);
	void setIsRegistered(const bool isRegistered);
	string getNickname() const;
	string getUserName() const;
	string getPasswd() const;
	string getBuffer() const;
	bool getIsRegistered() const;
	int getFd();

private:
	string nickname;
	string userName;
	string passwd;
	string buffer;
	bool isRegistered;
	int	fd;
};

#endif