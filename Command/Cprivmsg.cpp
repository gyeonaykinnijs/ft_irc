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

	if (user->getIsRegistered() == false)
	{
		// 에러 메시지 보내야 됨
		cout << "it should be registered" << endl;
		return ;
	}	
	if (param.size() < 1)
	{
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "No Param");
		network.sendToUser(*user, msg);
		return;
	}
	else if (param.size() > 1)
	{
		string msg = UserManager::makeMessage(ERR_TOOMANYTARGETS, user->getNickname(), "Too Many Targets");
		network.sendToUser(*user, msg);
		return;
	}
	string targetUser = param[0];
	Channel *channel = user->getChannel();
	User *target = channel->selectJoinUser(targetUser);
	if (!target)
	{
		string msg = UserManager::makeMessage(ERR_NOSUCHNICK, user->getNickname(), "no such nick");
		network.sendToUser(*user, msg);
		return;
	}
	else
	{
		network.sendToUser(*target, commandChunk.parameterLast);
	}
}