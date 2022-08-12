#include "Cmode.hpp"

void Cmode::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
    User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;

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
	if (param.size() == 2)
	{
		return;
	}
	if (param.size() != 3)
	{
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Need Three parameters");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	if (param[1] != "+o")
	{
		string msg = UserManager::makeMessage(ERR_UMODEUNKNOWNFLAG, user->getNickname(), "UNKNOWN FLAG ERROR");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	const string channelName = param[0];
	Channel *channel = user->getChannel(channelName);
	map<string, User *> userList = channel->getJoinUser();
	User *tempUser = userList[param[2]];
	channel->addOperator(tempUser->getFd());
	string msg = UserManager::makeMessage(RPL_MODE, channel->getChannelName() + " +o " + tempUser->getNickname(),  "");
	network.sendToUser2(user->getFd(), msg);
	string msg4 = UserManager::makeMessage(RPL_MODE, param[0], "");
	network.sendToOtherInChannel(*channel, user->getFd(),":" + tempUser->getNickname() + "!" + tempUser->getUserName() + "@127.0.0.1 " + msg4);

}