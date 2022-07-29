#ifndef __CPASS_HPP__
#define __CPASS_HPP__

#include "./ICommand.hpp"

class Cpass: public ICommand
{
public:
	void Cpass::execute(ChannelManager&, UserManager&, Network&, struct CommandChunk);
};

#endif