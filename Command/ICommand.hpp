#ifndef __ICOMMAND_H__
#define __ICOMMAND_H__

#include "../Network/Network.hpp"

class ICommand
{
public:
	virtual void execute(struct commandReq) = 0;
	virtual ~ICommand() {}
};

#endif