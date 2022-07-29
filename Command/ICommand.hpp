#ifndef __ICOMMAND_H__
#define __ICOMMAND_H__

#include "../Network/Network.hpp"
#include "../Channel/ChannelManager.hpp"
#include "../User/UserManager.hpp"

class ICommand
{
public:
	virtual void execute(ChannelManager &channelManager, UserManager &userManager, Network &network, struct CommandChunk commandChunk) = 0;
	virtual ~ICommand() {}
};

#endif