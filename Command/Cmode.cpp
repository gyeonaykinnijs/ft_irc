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
	// const string channelName = param[0];
	// Channel *channel = user->getChannel(channelName);
	// string target = param[0];
	// User *targetUser = userManager.getUserByNickname(target);
	// if (!targetUser)
	// {
	// 	string msg = UserManager::makeMessage(ERR_NOSUCHNICK, user->getNickname(), "No Such Nick");
	// 	network.sendToUser2(user->getFd(), msg);
	// 	return;
	// }
	// if (channel->getAdmin() == user)
	// {
		//string msg = UserManager::makeMessage(":" + user->getNickname() + "!" + user->getUserName() + "@127.0.0.1 " + RPL_JOIN, param[0], "");
		string msg = UserManager::makeMessage(":" + user->getNickname() + "!~" + user->getUserName() + "@127.0.0.1 " + "MODE" , param[0], "+s");// + user->getUserName(),  "");
		network.sendToUser2(user->getFd(), msg);
	//}


	// string msg = "";
	// if (commandChunk.parameterLast.empty() && !param[1].empty())
	// 	msg = UserManager::makeMessage("PRIVMSG", targetChannel->getChannelName(), param[1]);
	// else 
	// 	msg = UserManager::makeMessage("PRIVMSG", targetChannel->getChannelName(), commandChunk.parameterLast);	

	// string msg2 = UserManager::makeMessage("MODE" , user->getNickname()+ " @ " + channel->getChannelName(), list);
	// network.sendToUser2(user->getFd(), msg2);
	return ;

}