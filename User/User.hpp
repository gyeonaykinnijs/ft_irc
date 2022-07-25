#ifndef __User_H__
#define __User_H__
#include <string>

class User{
public:
	User();
	User(const std::string nickname, const std::string userName);
	~User();

	void setNickName(const std::string nickName);
	void setUserName(const std::string userName);
	void setUserFd(const size_t userFd);
	std::string getNickName();
	std::string getUserName();
	size_t getUserFd();

private:
	std::string nickName;
	std::string userName;
	size_t		userId;
	size_t		participateChannelFd;
	int		fd;
	
};

#endif