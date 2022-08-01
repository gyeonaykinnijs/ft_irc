#include "Cjoin.hpp"

void Join::execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	

	string channelName = param.at(0);
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
		channel = channelManager.createChannel(channelName, password, user);
	}

	if (channel->getMaxSizeUser() > 0 && channel->getCurSizeUser() >= channel->getMaxSizeUser()){
		
		/* channel number full error */
		string msg = UserManager::makeMessage(ERR_CHANNELISFULL , user->getNickname(), "channel is full");
		network.sendToUser(*user, msg);
		return;
	}

	if (channel->getChannelKey() != password) {
		/* no match password error */
		string msg = UserManager::makeMessage(ERR_BADCHANNELKEY , user->getNickname(), "no match password error");
		network.sendToUser(*user, msg);
		return;
	}

	/**
	 * @brief 
	 * 			
	 * 			channel에 사람 넣기 
	 * 			+
	 * 			사람에 channel 넣기
	 * 
	 */


}