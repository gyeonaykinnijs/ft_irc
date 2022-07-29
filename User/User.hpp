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
	void setChannel(const Channel *channel);


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
	

	/*

		Ennum;

	*/

	enum Auth
	{
		ADMIN, NORMAL
	};


private:
	string nickname;
	string userName;
	string realName;
	string passwd;
	string buffer;
	Channel *channel;
	Auth auth;
	bool isRegistered;
	int	fd;
};

#endif