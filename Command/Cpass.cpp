#include "./Cpass.hpp"

void Cpass::execute(ChannelManager &channelManager, UserManager &userManager, Network &network, struct CommandChunk commandChunk)
{
	User *tmpUser = userManager.getUserByFd(commandChunk.fd);

	if (tmpUser->getIsRegistered())
	{
		string errMessage = ":" + prefix + " " + ERR_ALREADYREGISTERED 
					+ tmpUser->getNickname() + 
		network.sendToUser(*tmpUser, errMessage);
	}
	else if (commandChunk.parameters.size() == 0)
	{
		network.sendToUser(*tmpUser, err_message);
		return sendError(ERR_NEEDMOREPARAMS);
	} 
	else
	{
		std::string password = commandChunk.parameters[0];
		tmpUser->setPasswd(password);
	}
}