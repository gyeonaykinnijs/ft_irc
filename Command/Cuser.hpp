#ifndef __CUSER_H__
#define __CUSER_H__

#include "../Network/Network.hpp"
#include "./ICommand.hpp"

class Cuser: public ICommand
{
public:
	static void execute(const struct CommandChunk commandChunk);
};


#endif