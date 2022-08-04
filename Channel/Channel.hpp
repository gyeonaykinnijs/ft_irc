#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include "../defines.hpp"

class User;

class Channel
{

public:
	Channel();
	~Channel();
	Channel(const std::string channelName);
	void setChannelName(const string channelName);
	void setAdmin(User *user);
	void setChannelKey(const string channelKey);
	void setCurSizeUser(const int size);
	string getChannelName() const;
	User* getAdmin();
	string getChannelKey() const;
	int getCurSizeUser() const;
	int getMaxSizeUser() const;
	void insertJoinUser(User *user);
	User* selectJoinUser(string userName);
	void deleteJoinUser(User *user);
	std::map<string, User *> getJoinUser();
	enum Mode
	{
		WAIT, TALKING, ELSE
	};

private:
	string channelName;
	string channelKey;
	User *admin; // 채널 만든 사람
	map<string, User *> joinUser; // 채널에 참가하고 있는 유저 리스트
	int maxSizeUser;
	int curSizeUser;
};

#endif