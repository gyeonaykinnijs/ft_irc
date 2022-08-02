#include "Cjoin.hpp"

void Cjoin::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;

	if (user->getIsRegistered() == false)
	{
		// 에러 메시지 보내야 됨
		cout << "it should be registered" << endl;
		return ;
	}	
	if (param.size() == 0)
	{
		cout << "need more parameters" << endl;
		return ;
	}
	const string channelName = param[0];
	string password = param.size() > 1 ? param[1] : "";
	Channel *channel = user->getChannel();

	if (channel)
	{
		/* Too many channel ERROR */
		string msg = UserManager::makeMessage(ERR_TOOMANYCHANNELS, user->getNickname(), "Too many channel");
		network.sendToUser(*user, msg);
		return ;
	}
	channel = channelManager.getChannel(channelName);
	if (!channel)
	{
		channel = channelManager.createChannel(param[0], password, user);
	}
	if (channel->getMaxSizeUser() > 0 && channel->getCurSizeUser() >= channel->getMaxSizeUser())
	{	
		/* channel number full error */
		string msg = UserManager::makeMessage(ERR_CHANNELISFULL , user->getNickname(), "channel is full");
		network.sendToUser(*user, msg);
		return;
	}

	if (channel->getChannelKey() != password)
	{
		/* no match password error */
		string msg = UserManager::makeMessage(ERR_BADCHANNELKEY , user->getNickname(), "no match password error");
		network.sendToUser(*user, msg);
		return;
	} 
	channel->insertJoinUser(user);
	user->setChannel(channel);
	string msg = UserManager::makeMessage("???" , user->getNickname(), "channel make and channel in user");
	network.sendToUser(*user, msg);

}