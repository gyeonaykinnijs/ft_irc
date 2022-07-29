#include "./Cnick.hpp"

void sendError(string errorMessage)
{
	
}

void execute(ChannelManager& channelManager, UserManager& userManager, Network& network, struct CommandChunk commandChunk)
{  // 최대길이 9
	User *tmpUser = userManager.getUserByFd(commandChunk.fd);
	
	if (tmpUser->getIsRegistered()) // 이미 등록했고 nick 변경할 때
	{

	}
}
 