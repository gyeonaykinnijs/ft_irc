#ifndef __CNICK_H__
#define __CNICK_H__

#include "./ICommand.hpp"

class Cnick: public ICommand
{
public:
	static void execute(const struct CommandChunk commandChunk);
};

#endif