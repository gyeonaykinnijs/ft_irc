#ifndef __QUIT_HPP__
#define __QUIT_HPP__

#include "ICommand.hpp"

#include <string>
#include "./ICommand.hpp"

using namespace std;

class Quit : public ICommand
{
public:
	void execute(ChannelManager &channelManager, UserManager &userManager, Network &network, struct CommandChunk commandChunk);
};

#endif