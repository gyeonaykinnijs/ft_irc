#ifndef __KICK_HPP__
#define __KICK_HPP__


#include <string>
#include "./ICommand.hpp"

using namespace std;

class Kick : public ICommand
{
public:
	void execute(ChannelManager &channelManager,
				UserManager &userManager,
				Network &network,
				struct CommandChunk commandChunk);
};

#endif