#ifndef __USER_HPP__
#define __USER_HPP__
#include "../defines.hpp"
#include "../Channel/Channel.hpp"

class User
{


public:
	/*

		Ennum;

	*/

	enum Auth
	{
		ADMIN, NORMAL
	};


	User();
	User(const string nickname, const string userName);
	~User();

	/*

		Setter

	*/
	void setNickname(const string nickName);
	void setUserName(const string userName);
	void setFd(const int fd);
	void setPasswd(const string passwd);
	void setBuffer(const string buffer);
	void setIsRegistered(const bool isRegistered);
	void setChannel(Channel *channel);
	void setAuth(const User::Auth auth);

	/*

		Getter

	*/

	Channel *getChannel();
	string getNickname() const;
	string getUserName() const;
	string getPasswd() const;
	string getBuffer() const;
	User::Auth getAuth() const;
	bool getIsRegistered() const;
	int getFd() const;
	

	
	void appendBuffer(string buffer);



private:

	/*
		기본 정보
	*/
	string nickname;
	string userName;
	string realName;
	string passwd;
	int	fd;
	Auth auth;

	/*

	*/
	string buffer;
	Channel *channel;
	bool isRegistered;

};

#endif