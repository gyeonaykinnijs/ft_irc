#ifndef __CKILL_HPP__
#define __CKILL_HPP__


#include <string>
#include "./ICommand.hpp"

using namespace std;

class Ckill : public ICommand
{
public:
	void execute(ChannelManager &channelManager,
				UserManager &userManager,
				Network &network,
				struct CommandChunk commandChunk);
};

#endif