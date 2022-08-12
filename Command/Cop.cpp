#include "Cop.hpp"

void Cop::execute(ChannelManager &channelManager,
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
	if (param.size() < 3)
	{	// 인자 부족
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Not enough parameters");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	string channelName = param[0];
	Channel *channel = channelManager.getChannel(channelName);
	map<string, User *> userList = channel->getJoinUser();
	if (!channel)
	{	// channel 없을 때
		string msg = UserManager::makeMessage(ERR_NOSUCHCHANNEL, user->getNickname(), "No Such Channel");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	if (channel->getOperators().count(user->getFd()) == 0)
	{	// 강퇴하는 사람이 방장인지 검사
		string msg = UserManager::makeMessage(ERR_CHANOPRIVSNEEDED, user->getNickname(), "Need Operation");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	for (unsigned long i = 1; i < param.size(); i++)
	{
		User *tempUser = userList[param[i]];
		if (!tempUser)
		{
			string msg = UserManager::makeMessage(ERR_USERNOTINCHANNEL, param[i], "No Such User in Channel");
			network.sendToUser2(user->getFd(), msg);
		}
		else
		{
			channel->addOperator(tempUser->getFd());
			string msg = UserManager::makeMessage(RPL_MODE, channel->getChannelName() + " +o " + param[0],  "");
			network.sendToUser2(user->getFd(), msg);
		}
	}
}