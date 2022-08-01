#include "Cping.hpp"

/**
 * @brief 
 * 
 * @param channelManager 
 * @param userManager 
 * @param network 
 * @param commandChunk 
 * 
 * 
 * 			:irc.example.com 001 borja :Welcome to the Internet Relay Network borja!borja@polaris.cs.uchicago.edu
			:irc.example.com 433 * borja :Nickname is already in use.
			:irc.example.org 332 borja #cmsc23300 :A channel for CMSC 23300 students
 * 
 */


void Ping::execute(ChannelManager &channelManager,
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
		 */

		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "No Param");
		network.sendToUser(*user, msg);
		return;
	}

	string buffer = " PONG :" + param.at(0) + "\r\n";
	network.sendToUser(*user, buffer.c_str());
}
