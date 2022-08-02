#ifndef __USER_HPP__
#define __USER_HPP__
#include "../defines.hpp"
#include "../Channel/Channel.hpp"

class User
{
public:
	enum Auth
	{
		ADMIN, NORMAL
	};

	User();
	User(const string nickname, const string userName);
	~User();
	void setNickname(const string nickName);
	void setUserName(const string userName);
	void setFd(const int fd);
	void setRealName(const string realName);
	void setPasswd(const string passwd);
	void setBuffer(const string buffer);
	void setIsRegistered(const bool isRegistered);
	void setChannel(Channel *channel);
	void setAuth(const User::Auth auth);
	void setIgnored(const bool ignore);
	Channel *getChannel() const;
	string getNickname() const;
	string getUserName() const;
	string getPasswd() const;
	string getBuffer() const;
	string getRealName() const;
	User::Auth getAuth() const;
	bool getIsRegistered() const;
	int getFd() const;
	bool getIgnored() const;
	void appendBuffer(string buffer);

private:
	string nickname;
	string userName;
	string realName;
	string passwd;
	int	fd;
	Auth auth;
	string buffer;
	Channel *channel;
	bool isRegistered;
	bool ignored;
};

#endif