#include "./Cpass.hpp"

void Cpass::execute(ChannelManager &channelManager, UserManager &userManager, Network &network, struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	(void)channelManager;
	
	if (user->getIsRegistered())
	{	// 접속되었는데 pass 또 입력할 때
		string msg = UserManager::makeMessage(ERR_ALREADYREGISTERED, user->getNickname(), "User is already registered");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	else if (user->getPassOK())
	{	// 비밀번호 맞아서 접속됐는데 또 pass 입력했을 때
		string msg = UserManager::makeMessage(ERR_ALREADYCONNECTED, "*", "User doesn't need password anymore");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	else if (commandChunk.parameters.empty())
	{	// 인자 더 필요할 때
		string msg = UserManager::makeMessage(ERR_NEEDMOREPARAMS, user->getNickname(), "Not enough parameters");
		network.sendToUser2(user->getFd(), msg);
		return;
	}
	else
	{
		string password = commandChunk.parameters[0];
		user->setPasswd(password);
	}
}