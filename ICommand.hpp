#ifndef __ICOMMAND_HPP__
#define __ICOMMAND_HPP__

class ICommand
{
public:
	virtual void execute() = 0;
	virtual ~ICommand() {}
};

#endif