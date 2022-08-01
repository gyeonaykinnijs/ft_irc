#include "Cpong.hpp"

void Pong::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
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

	string buffer = " PONG :" + param.at(0) + "\r\n";
	network.sendToUser(*user, buffer.c_str());
}