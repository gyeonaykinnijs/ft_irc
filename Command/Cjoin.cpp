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
	string msg = UserManager::makeMessage(RPL_JOIN, user->getNickname(), "channel make and channel in user");
	network.sendToUser2(user->getFd(), msg);
}