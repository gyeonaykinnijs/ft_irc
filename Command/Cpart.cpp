#include "Cpart.hpp"


/*
### PART
	`PART <channels> [<message>]`
	- 사용자가 쉼표로 구분된 목록 <channels>의 채널을 떠나도록 합니다.
	- RFC 1459에 정의되어 있습니다.
*/

void Cpart::execute(ChannelManager &channelManager,
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
	string channelName = param[0];
	if (channelName[0] != '#')
	{
		channelName = '#' + channelName;
	}
	Channel *channel = channelManager.getChannel(channelName);
	if (!channel) 
	{
		string msg = UserManager::makeMessage(ERR_NOSUCHCHANNEL, user->getNickname(), "No Such Channel");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	if (!user->getChannel(channelName)) 
	{
		string msg = UserManager::makeMessage(ERR_NOTONCHANNEL, user->getNickname(), "Not On Channel");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	string msg = UserManager::makeMessage(":" + user->getNickname() + "!" + user->getUserName() + "@127.0.0.1 " + RPL_PART, param[0], "");
	network.sendToChannel(*channel, msg);
	channel->deleteJoinUser(user);
	user->deleteChannel(channelName);
	channel->deleteOperator(user->getFd());
	// network.sendToUser2(user->getFd(), msg);
	// string msg4 = UserManager::makeMessage(RPL_PART, param[0], "");
	// network.sendToOtherInChannel(*channel, user->getFd(),":" + user->getNickname() + "!" + user->getUserName() + "@127.0.0.1 " + msg4);
}