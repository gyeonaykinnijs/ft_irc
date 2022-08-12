#ifndef __COP_HPP__
#define __COP_HPP__


#include <string>
#include "./ICommand.hpp"

using namespace std;

class Cop: public ICommand
{
public:
	void execute(ChannelManager &channelManager,
				UserManager &userManager,
				Network &network,
				struct CommandChunk commandChunk);
};

#endif