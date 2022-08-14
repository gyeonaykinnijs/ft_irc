#include "./Cuser.hpp"

void Cuser::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;

	if (user->getPassOK() == false)
	{		
		string msg = UserManager::makeMessage(ERR_NOTCONNECTED, "*", "User should be connected first");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	else if (user->getIsRegistered())
	{
		string msg = UserManager::makeMessage(ERR_ALREADYREGISTERED, user->getNickname(), "User is already registered");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	else if (param.size() < 3)
	{
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Not enough parameters");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	else
	{
		user->setUserName(param[0]);
		if (commandChunk.parameterLast.empty() && !param[1].empty())
			user->setRealName(param[1]);
		else 
			user->setRealName(commandChunk.parameterLast);
		user->setUserOK(true);
	}
}
