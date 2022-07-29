#ifndef __CUSER_HPP__
#define __CUSER_HPP__

#include "../Network/Network.hpp"
#include "./ICommand.hpp"

class Cuser: public ICommand
{
public:
	static void execute(const struct CommandChunk commandChunk);
};


#endif