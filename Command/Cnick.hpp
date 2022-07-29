#ifndef __CNICK_HPP__
#define __CNICK_HPP__

#include "./ICommand.hpp"

class Cnick: public ICommand
{
public:
	void execute(ChannelManager&, UserManager&, Network&, struct CommandChunk);
};

#endif