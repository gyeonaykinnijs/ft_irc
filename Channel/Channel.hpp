#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <string>
#include <vector>
#include <map>
#include <./User/User.hpp>

using namespace std;

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
	void addJoinUser(User user);
	void deleteJoinUser(User user);
	vector<User *> getJoinUser();

private:
	string channelName;
	size_t channelId;
	map<string, User *> joinUser;
};

#endif