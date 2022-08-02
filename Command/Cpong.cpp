#include "Cpong.hpp"

void Cpong::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;
	
	if (param.empty())
	{
		/**
		 * @brief 
		 * 			need more param
		 * 
		 * 
		 */

		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "No Param");
		network.sendToUser(*user, msg);
		return ;
	}

	string msg = " PONG :" + param[0] + "\r\n";
	network.sendToUser(*user, msg);
}