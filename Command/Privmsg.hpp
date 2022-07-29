#ifndef __PRIVMSG_HPP__
#define __PRIVMSG_HPP__

#include <string>

#include "ICommand.hpp"

class Privmsg : public ICommand
{
public:
	void execute(ChannelManager &channelManager,
				UserManager &userManager,
				Network &network,
				struct CommandChunk commandChunk);
};

#endif