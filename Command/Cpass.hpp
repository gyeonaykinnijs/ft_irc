#ifndef __CPASS_H__
#define __CPASS_H__

#include "../defines.hpp"

class Cpass: public ICommand
{
public:
	void Cpass::execute(ChannelManager&, UserManager&, Network&, struct CommandChunk);
};

#endif