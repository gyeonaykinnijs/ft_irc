#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <string>
#include <vector>
#include <map>
#include <./User/User.hpp>

class Channel{

public:
	Channel();
	~Channel();


	enum Status
	{
		WAIT,
		TAKING
	};

	void setChannelName(const std::string channelName);
	void setChannelId(size_t channelId);
	std::string getChannelName();
	size_t getChannelId();
	void addJoinUser(User user);
	void deleteJoinUser(User user);
	std::vector<User *> getJoinUser();

private:
	std::string channelName_;
	size_t channelId_;
	std::map<std::string, User *> joinUser_;
};

#endif