#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "defines.hpp"

class Server
{
public:
    Server();
    void init();
    void run();
    ~Server();

private:
    map<string, ICommand *> commands;
    ChannelManager channelManager;
    UserManager userManager;
    Network network;

    int callCommand(struct CommandChunk commandChunk);
};


#endif