#ifndef __COPER_HPP__
#define __COPER_HPP__


#include <string>
#include "./ICommand.hpp"

using namespace std;

class Coper : public ICommand
{
public:
	void execute(ChannelManager &channelManager,
				UserManager &userManager,
				Network &network,
				struct CommandChunk commandChunk);
};

#endif