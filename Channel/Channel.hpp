#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include "../defines.hpp"
#include "../User/User.hpp"
class Channel
{

public:
	Channel();
	~Channel();


	class mode
	{
	public:

	private:

	};

	void setChannelName(const string channelName);
	void setMakeUser(const User *user);
	void setChannelKey(const string channelKey);
	void setCurSizeUser(const int size);



	string getChannelName() const;
	User* getMakeUser() const;
	string getChannelKey() const;
	int getCurSizeUser() const;
	int getMaxSizeUser() const;



	void addJoinUser(User *user);
	void deleteJoinUser(User user);
	std::map<string, User *> getJoinUser();

private:
	string channelName;
	User *makeUser;
	string channelKey;
	map<string, User *> joinUser;
	int maxSizeUser;
	int curSizeUser;
};

#endif