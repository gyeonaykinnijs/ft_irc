#ifndef __PING_HPP__
#define __PING_HPP__

#include <string>
#include "./ICommand.hpp"

class Ping : public ICommand
{
public:
	void execute(ChannelManager &channelManager, UserManager &userManager, Network &network, struct CommandChunk commandChunk);
};

#endif