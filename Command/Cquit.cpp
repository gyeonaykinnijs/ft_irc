#include "Cquit.hpp"
#include <unistd.h>

void Cquit::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	(void)channelManager;

	if (user->getIsRegistered() == false)
	{
		string msg = UserManager::makeMessage(NULL, ERR_NOTREGISTERED, user->getNickname(), "You should register first");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	map<string, Channel*>::iterator iter = user->getChannelList().begin();
	map<string, Channel*>::iterator iterEnd = user->getChannelList().end();
	string last = commandChunk.parameterLast;
	string reason = ":" + (last.size() == 0 ? "Leaving..." : last);
	for (;iter != iterEnd; iter++)
	{
		string msg = UserManager::makeMessage(user, RPL_QUIT, reason, "");
		network.sendToOtherInChannel(*iter->second, user->getFd(), msg);
	}
	map<string, Channel *> channels = user->getChannelList();
	map<string, Channel *>::iterator iter2 = channels.begin();
	map<string, Channel *>::iterator iterEnd2 = channels.end();
	Channel* channel;
	for (; iter2 != iterEnd2; iter2++)
	{
		channel = channelManager.getChannel(iter2->second->getChannelName());
		channel->deleteJoinUser(user);
	}
	int fd = user->getFd();
	userManager.deleteUser(fd);
	close(fd);
}