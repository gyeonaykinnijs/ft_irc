#include "Cpong.hpp"

void Cpong::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;

	string msg = " PING :" + param[0] + "\r\n";
	network.sendToUser(user->getFd(), msg);
}