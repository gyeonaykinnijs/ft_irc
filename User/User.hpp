#ifndef __User_H__
#define __User_H__
#include <string>
#include <vector>

class User{
public:
	User();
	User(const std::string nickname, const std::string userName);
	~User();

	void setNickName(const std::string nickName);
	void setUserName(const std::string userName);
	void setUserId(const size_t userId);
	void setFd(const int fd);
	std::string getNickName();
	std::string getUserName();
	size_t getUserId();
	int getFd();

private:
	std::string nickName;
	std::string userName;
	size_t		userId;
	size_t		participateChannelId;
	int			fd;
};

#endif