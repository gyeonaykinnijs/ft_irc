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
		string msg = UserManager::makeMessage(ERR_NOTREGISTERED, user->getNickname(), "You should register first");
		network.sendToUser2(user->getFd(), msg);
		return;
	}	
	std::string reason = param.empty() ? "Leaving..." : param[0];
	reason = reason[0] == ':' ? reason.substr(1) : reason;
	map<string, Channel*>::iterator iter = user->getChannelList().begin();
	map<string, Channel*>::iterator iterEnd = user->getChannelList().end();

	for (;iter != iterEnd; iter++)
	{
		string msg4 = UserManager::makeMessage("QUIT", ":Quit: Leaving...", "");
		network.sendToOtherInChannel(*iter->second, user->getFd(),":" + user->getNickname() + "!" + user->getUserName() + "@127.0.0.1 " + msg4);
	}
	map<string, Channel *> channel = user->getChannelList();
	map<string, Channel *>::iterator iter2 = channel.begin();
	map<string, Channel *>::iterator iterEnd2 = channel.end();
	for (; iter2 != iterEnd2; iter2++)
	{
		channelManager.getChannel(iter2->second->getChannelName())->deleteJoinUser(user);
	}
	userManager.deleteUser(user->getFd());
	close(user->getFd());
}