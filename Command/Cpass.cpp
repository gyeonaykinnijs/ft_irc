#include "./Cpass.hpp"

void Cpass::execute(ChannelManager &channelManager, UserManager &userManager, Network &network, struct CommandChunk commandChunk)
{
	User *tmpUser = userManager.getUserByFd(commandChunk.fd);
	if (tmpUser->isRegistered())
	{
		return sendError(ERR_ALREADYREGISTERED);
	}
	else if (commandChunk.parameters.size() == 0)
	{
		return sendError(ERR_NEEDMOREPARAMS);
	}
	else
	{
		std::string password = commandChunk.parameters[0];
		tmpUser->setPasswd(password);
	}
}