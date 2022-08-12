#include "Cprivmsg.hpp"

void Cprivmsg::execute(ChannelManager &channelManager,
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
	if (param.size() < 1)
	{
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Not enough parameters");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	string target = param[0];
	if (target[0] == '#')
	{
		Channel *targetChannel = channelManager.getChannel(target);
		if (!targetChannel)
		{
			string msg = UserManager::makeMessage(ERR_NOSUCHCHANNEL, user->getNickname(), "No such channel");
			network.sendToUser2(user->getFd(), msg);
			return;
		}
		else if (targetChannel->getJoinUser().count(user->getNickname()) == 0)
		{
			string msg = UserManager::makeMessage(ERR_USERNOTINCHANNEL, user->getNickname(), "User Not In Channel");
			network.sendToUser2(user->getFd(), msg);
			return;
		}
		else
		{
			string msg = "";
			if (commandChunk.parameterLast.empty() && !param[1].empty())
			{
				msg = UserManager::makeMessage(RPL_PRIVMSG, targetChannel->getChannelName(), param[1]);
			}
			else
			{
				msg = UserManager::makeMessage(RPL_PRIVMSG, targetChannel->getChannelName(), commandChunk.parameterLast);
			}
			network.sendToOtherInChannel(*targetChannel, user->getFd(), ":" + user->getNickname() + "!" + user->getUserName() + "@127.0.0.1 " + msg);
			return ;
		}
	}
	else
	{

		User *targetUser = userManager.getUserByNickname(target);
		if (!targetUser)
		{
			string msg = UserManager::makeMessage(ERR_NOSUCHNICK, user->getNickname(), "No Such Nick");
			network.sendToUser2(user->getFd(), msg);
			return;
		}
		else
		{
			string msg = UserManager::makeMessage(RPL_PRIVMSG, targetUser->getNickname(), commandChunk.parameterLast);
			network.sendToUser2(targetUser->getFd(), msg);
			return ;
		}
	}
}