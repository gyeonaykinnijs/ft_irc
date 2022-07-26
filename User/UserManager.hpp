#ifndef __UserManager_H__
#define __UserManager_H__

#include "User.hpp"
#include <vector>
#include <map>
#include <string>

class UserManager{

public:
	UserManager();
	~UserManager();
	User* getUser(std::string userName);
	void setUser(User user);
private:
	std::map<std::string, User *> userList;
};

#endif