#ifndef __ICOMMAND_H__
#define __ICOMMAND_H__

class ICommand
{
public:
	virtual void execute() = 0;
	virtual ~ICommand() {}
};

#endif