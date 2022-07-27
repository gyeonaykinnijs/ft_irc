#ifndef __USER_H__
#define __USER_H__
#include <string>
#include <vector>
using namespace std;

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
	string getNickname();
	string getUserName();
	string getPasswd();
	int getFd();

private:
	string nickname;
	string userName;
	string passwd;
	int	fd;
};

#endif