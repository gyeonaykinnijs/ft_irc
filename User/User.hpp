#ifndef __USER_HPP__
#define __USER_HPP__
#include "../defines.hpp"
#include "../Channel/channel.hpp"

class User
{


public:
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


	/*

		Getter

	*/

	Channel *getChannel() const;
	string getNickname() const;
	string getUserName() const;
	string getPasswd() const;
	string getBuffer() const;
	bool getIsRegistered() const;
	int getFd() const;
	

	
	void appendBuffer(string buffer);

	/*

		Ennum;

	*/

	enum Auth
	{
		ADMIN, NORMAL
	};


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