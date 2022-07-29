#include "Join.hpp"

void Join::execute(ChannelManager &channelManager, UserManager &userManager, Network &network, struct CommandChunk commandChunk)
{
	User *user = userManager.getUserByFd(commandChunk.fd);
	vector<string> param = commandChunk.parameters;
	

	std::string name = param.at(0);
	std::string password = param.size() > 1 ? param[1] : "";
	
	Channel *channel = user->getChannel();
	

	if (channel)
	{
		/* Too manay channel ERROR */
		return ;
	}
	channel = channelManager.getChannel(name);
	if (!channel)
		channel = channelManager.createChannel(name, password, user);

	if (channel->getMaxSizeUser() > 0 && channel->getCurSizeUser() >= channel->getMaxSizeUser()){
		
		/* channel number full error */

		return;
	}

	if (channel.getPassword() != password) {
		/* no match password error */
		return;
	}


	

	

}