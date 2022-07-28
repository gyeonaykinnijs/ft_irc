#ifndef __CPASS_H__
#define __CPASS_H__

#include "../Network/Network.hpp"
#include "./ICommand.hpp"

class Cpass: public ICommand
{
public:
	static void execute(const struct CommandChunk commandChunk);
};

#endif