#ifndef __UserManager_H__
#define __UserManager_H__

#include "User.hpp"
#include <vector>
#include <map>

class UserManager{

public:
	std::map<size_t, User *> userList;
	
	UserManager();
	~UserManager();
	void getUser();
	void setUser();
};

#endif