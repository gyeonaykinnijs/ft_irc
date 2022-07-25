#ifndef __Channel_H__
#define __Channel_H__

#include <string>
#include <vector>
#include <User/User.hpp>

class Channel{

public:

	std::vector<User &> joinUser;

	Channel();
	~Channel();


	enum Status
	{
		WAIT,
		TAKING
	};

	void setChannelName(const std::string channelName);
	std::string getChannelName();

private:
	std::string channelName;
	size_t channelId;
};

#endif