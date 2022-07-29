#ifndef __OPER_HPP__
#define __OPER_HPP__


#include <string>
#include "./ICommand.hpp"

using namespace std;

class Oper : public ICommand
{
public:
	void execute(ChannelManager &channelManager,
				UserManager &userManager,
				Network &network,
				struct CommandChunk commandChunk);
};

#endif