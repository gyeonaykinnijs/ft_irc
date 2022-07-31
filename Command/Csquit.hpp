#ifndef __CSQUIT_HPP__
#define __CSQUIT_HPP__

#include <string>
#include "./ICommand.hpp"

using namespace std;

class Squit : public ICommand
{
public:
	void execute(ChannelManager &channelManager,
				UserManager &userManager,
				Network &network,
				struct CommandChunk commandChunk);
};

#endif