#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include "../defines.hpp"
#include "../User/User.hpp"
class Channel
{

public:
	Channel();
	~Channel();


	enum Status
	{
		WAIT,
		TAKING
	};

	void setChannelName(const string channelName);
	void setChannelId(size_t channelId);
	string getChannelName();
	size_t getChannelId();
	void addJoinUser(User *user);
	void deleteJoinUser(User user);
	std::map<string, User *> getJoinUser();

private:
	string channelName;
	size_t channelId;
	map<string, User *> joinUser;
};

#endif