#include "Cnotice.hpp"


void Cnotice::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
    User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;

	if (user->getIsRegistered() == false)
	{
		// 에러 메시지 보내야 됨
		cout << "it should be registered" << endl;
		return ;
	}	
	if (param.size() < 1)
	{
		return;
	}
	else if (param.size() > 1)
	{
		return;
	}
	string targetUser = param[0];
	User *target = userManager.getUserByNickname(targetUser);
	if (!target)
	{
		return;
	}
	else
	{
		network.sendToUser(*target, commandChunk.parameterLast);
	}
}