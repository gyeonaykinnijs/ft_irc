#ifndef __CHANNELMANAGER_H__
#define __CHANNELMANAGER_H__

#include "Channel.hpp"
#include <map>
using namespace std;

class ChannelManager
{
public:
	ChannelManager();
	~ChannelManager();
	/*
		Getter
	*/
	Channel* getChannel(string channelName);

	/**
	 * @brief 
	 * Create
	 */
	Channel *createChannel(string channelName, string passwd, User *user);


	/**
	 * @brief 
	 * Delete
	 */
	void deleteChannel(string channelName);

private:
	map<string, Channel *> channel_list;
};

#endif