#ifndef __CNICK_HPP__
#define __CNICK_HPP__

#include "./ICommand.hpp"

class Cnick: public ICommand
{
public:
	void execute(ChannelManager &channelManager,
					UserManager &userManager,
					Network &network,
					struct CommandChunk commandChunk);
					
	bool checkUserValidNickname(const string nickName);
};

#endif