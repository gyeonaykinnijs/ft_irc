#ifndef __JOIN_HPP__
#define __JOIN_HPP__


#include <string>
#include "./ICommand.hpp"

using namespace std;

class Join : public ICommand
{
public:
	void execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk);
};

#endif