#ifndef __CNICK_H__
#define __CNICK_H__

#include "../defines.hpp"

class Cnick: public ICommand
{
public:
	void execute(ChannelManager&, UserManager&, Network&, struct CommandChunk);
};

#endif