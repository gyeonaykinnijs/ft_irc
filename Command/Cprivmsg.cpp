#include "Cprivmsg.hpp"

/**
 * @brief 
 * 
 * 
 * 		### PRIVMSG
 * 		`PRIVMSG <msgtarget> :<message>`
 *		- 일반적으로 사용자 또는 채널인 <msgtarget>에 <message>를 보냅니다.
		- RFC 1459에 정의되어 있습니다.
 * 
 */

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
	else if (param.size() > 1)
	{
		string msg = UserManager::makeMessage(ERR_TOOMANYTARGETS, user->getNickname(), "Too Many Targets");
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
		else
		{
			string msg = UserManager::makeMessage("PRIVMSG", targetChannel->getChannelName(), commandChunk.parameterLast);
			network.sendToChannel(*targetChannel, msg);
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
			string msg = UserManager::makeMessage("PRIVMSG", targetUser->getNickname(), commandChunk.parameterLast);
			network.sendToUser2(targetUser->getFd(), msg);
		}
	}
}