#ifndef __USERMANAGER_H__
#define __USERMANAGER_H__

#include "User.hpp"
#include <vector>
#include <map>
#include <string>

class UserManager{

public:
	UserManager();
	~UserManager();
	User* getUser(std::string userNickName);
	User* getFdUser(int userNickName);
	void setUser(User user);
	void setfdUser(User user);
private:
	std::map<std::string, User *> userList_;
	std::map<int, User *> findFdUserList_;
};

#endif