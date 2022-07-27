#ifndef __PASS_H__
#define __PASS_H__

#include "../Network/Network.hpp"

class Pass: public ICommand
{
public:
	Pass();
	Pass(const Pass& copy);
	Pass& operator=(const Pass& origin);
	~Pass();

	void execute(const struct &commandChunk);
};



#endif