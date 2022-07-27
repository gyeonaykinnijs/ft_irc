#ifndef __NICK_H__
#define __NICK_H__

#include "../Network/Network.hpp"

class Nick: public ICommand
{
public:
	Nick();
	Nick(const Nick& copy);
	Nick& operator=(const Nick& origin);
	~Nick();

	execute(const struct commandChunk);
};


#endif