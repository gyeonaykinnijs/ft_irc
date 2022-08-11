#include "Cjoin.hpp"

void Cjoin::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;

	if (user->getIsRegistered() == false)
	{
		string msg = UserManager::makeMessage(ERR_NOTREGISTERED, user->getNickname(), "You should register first");
		network.sendToUser2(user->getFd(), msg);
		return;
	}	
	if (param.empty())
	{
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Not enough parameters");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	const string channelName = param[0];
	string password = param.size() > 1 ? param[1] : "";
	Channel *channel = user->getChannel(channelName);

	if (channel)
	{
		/* Too many channel ERROR */
		string msg = UserManager::makeMessage(ERR_TOOMANYCHANNELS, user->getNickname(), "Too many channel");
		network.sendToUser2(user->getFd(), msg);
		return ;
	}
	channel = channelManager.getChannel(channelName);
	if (!channel)
	{
		channel = channelManager.createChannel(param[0], password, user);
	}
	if (channel->getMaxSizeUser() > 0 && channel->getCurSizeUser() >= channel->getMaxSizeUser())
	{	
		/* channel number full error */
		string msg = UserManager::makeMessage(ERR_CHANNELISFULL , user->getNickname(), "channel is full");
		network.sendToUser2(user->getFd(), msg);
		return;
	}

	if (channel->getChannelKey() != password)
	{
		/* no match password error */
		string msg = UserManager::makeMessage(ERR_BADCHANNELKEY , user->getNickname(), "no match password error");
		network.sendToUser2(user->getFd(), msg);
		return;
	} 
	channel->insertJoinUser(user);
	user->addChannel(channel);
	string msg = UserManager::makeMessage(":" + user->getNickname() + "!" + user->getUserName() + "@127.0.0.1 " + RPL_JOIN, param[0], "");
	// network.sendToOtherInChannel(channel, user->getFd(), ":" + user->getNickname() + "!" + user->getUserName() + "@localhost " + RPL_JOIN + " :" + param[0]);
	string msg4 = UserManager::makeMessage(RPL_JOIN, param[0], "");
	//TODO:
	network.sendToUser2(user->getFd(), msg);
	network.sendToOtherInChannel(*channel, user->getFd(),":" + user->getNickname() + "!" + user->getUserName() + "@127.0.0.1 " + msg4);
	
	string list = "";
	map<string, User *> users = channel->getJoinUser();
	map<string, User *>::iterator iter = users.begin();
	map<string, User *>::iterator iterEnd = users.end();
	for (; iter != iterEnd; iter++)
	{
		if (iter != users.begin())
		{
			list += " ";
		}
		if (channel->getOperators().count(iter->second->getFd()) == 1)
		{
			list += "@";
		}
		list += iter->second->getNickname();
	}
	string msg2 = UserManager::makeMessage("353" , user->getNickname()+ " = " + channel->getChannelName(), list);
	network.sendToUser2(user->getFd(), msg2);
	// network.sendToOtherInChannel(*channel, user->getFd(),msg2);
	string msg3 = UserManager::makeMessage("366" , user->getNickname() + " " + channel->getChannelName(), "End of /NAMES list.");
	network.sendToUser2(user->getFd(), msg3);
	//network.sendToOtherInChannel(*channel, user->getFd(),msg3);
	
}