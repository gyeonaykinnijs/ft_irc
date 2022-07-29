#ifndef __PART_HPP__
#define __PART_HPP__


#include <string>
#include "./ICommand.hpp"

using namespace std;

class Part : public ICommand
{
public:
	void execute(ChannelManager &channelManager,
				UserManager &userManager,
				Network &network,
				struct CommandChunk commandChunk);
};

#endif