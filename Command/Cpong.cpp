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
		 */
		return;
	}

	std::string buffer = ":" + commandChunk.prefix  + " PONG :" + param.at(0) + "\r\n";
	
	if (send(user->getFd(), buffer.c_str(), buffer.length(), 0) < 0)
		throw std::runtime_error("Error while sending message to client.");
		
}