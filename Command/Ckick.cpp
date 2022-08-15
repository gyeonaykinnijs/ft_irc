#include "Ckick.hpp"

void Ckick::execute(ChannelManager &channelManager,
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
	if (param.size() != 2)
	{	// channel user 인자 두 개 있어야 함
		string msg = UserManager::makeMessage(NULL, ERR_NEEDMOREPARAMS, user->getNickname(), "Not enough parameters");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	string name = param[0];
	string targetUser = param[1];
	Channel *channel = user->getChannel(name);
	if (!channel)
	{	// channel 없을 때
		string msg = UserManager::makeMessage(NULL, ERR_NOSUCHCHANNEL, user->getNickname(), "No Such Channel");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	if (channel->getChannelName() != name)
	{	// 명령어 쓴 user가 channel의 멤버가 아닐 때
		string msg = UserManager::makeMessage(NULL, ERR_NOTONCHANNEL, user->getNickname(), "User is Not in Channel");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	if (channel->getOperators().count(user->getFd()) == 0)
	{	// 강퇴하는 사람이 operator인지 검사
		string msg = UserManager::makeMessage(NULL, ERR_CHANOPRIVSNEEDED, user->getNickname(), "Need Operation");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	User *target = channel->selectJoinUser(targetUser);
	if (!target)
	{	// 내보내려는 user가 channel에 있는지 확인
		string msg = UserManager::makeMessage(NULL, ERR_USERNOTINCHANNEL, user->getNickname(), "Target User is Not in Channel");
		network.sendToUser(user->getFd(), msg);
		return;
	}
	string msg = UserManager::makeMessage(user, RPL_KICK, channel->getChannelName() + " " + targetUser, "");
	network.sendToChannel(*channel, msg);
	target->deleteChannel(channel->getChannelName());
	channel->deleteJoinUser(target);
	channel->deleteOperator(user->getFd());
}
