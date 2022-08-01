#include "./Cnick.hpp"

void sendError(string errorMessage)
{
	
}

void execute(ChannelManager& channelManager, UserManager& userManager, Network& network, struct CommandChunk commandChunk)
{  // 최대길이 9
	User *tmpUser = userManager.getUserByFd(commandChunk.fd);
	string nickname = commandChunk.parameters[0];

	if (nickname.size() == 0) // 인자 부족할 때
	{
		return sendError(ERR_NEEDMOREPARAMS);
	}
	if (userManager.getUserByNickname(nickname) == NULL) // 불가능한 닉네임일 때
	{

	}
	if (nickname.size() > 9)
	{
		nickname = nickname.substr(9);
	}
	tmpUser->setNickname(nickname);
	if (tmpUser->getIsRegistered()) // 이미 등록했고 nick 변경할 때
	{
		network.sendToChannel(userManager::makeMessage())
	}

}