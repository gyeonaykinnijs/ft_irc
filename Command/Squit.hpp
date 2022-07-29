#ifndef __SQUIT_HPP__
#define __SQUIT_HPP__

#include "ICommand.hpp"

#include <string>
#include "./ICommand.hpp"

using namespace std;

class Squit : public ICommand
{
public:
	void execute(ChannelManager &channelManager, UserManager &userManager, Network &network, struct CommandChunk commandChunk);
};

#endif