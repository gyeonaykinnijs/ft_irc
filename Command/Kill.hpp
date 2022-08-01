#ifndef __KILL_HPP__
#define __KILL_HPP__


#include <string>
#include "./ICommand.hpp"

using namespace std;

class Kill : public ICommand
{
public:
	void execute(ChannelManager &channelManager,
				UserManager &userManager,
				Network &network,
				struct CommandChunk commandChunk);
};

#endif