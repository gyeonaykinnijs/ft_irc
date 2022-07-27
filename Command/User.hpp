#ifndef __USER_H__
#define __USER_H__

#include "../Network/Network.hpp"

class User: public ICommand
{
public:
	User();
	User(const User& copy);
	User& operator=(const User& origin);
	~User();

	execute(const struct commandChunk);
};


#endif