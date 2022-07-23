#ifndef __Channel_H__
#define __Channel_H__

#include <string>
#include <vector>
#include <User/User.hpp>

class Channel{

public:
	std::string name;
	std::vector<User &> joinUser;

	Channel();
	~Channel();


	enum Status
	{
		WAIT,
		TAKING
	};
	
};

#endif