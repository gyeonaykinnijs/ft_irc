#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "../defines.hpp"
#include "../User/UserManager.hpp"
#include "../Channel/ChannelManager.hpp"
#include "../Network/Network.hpp"

class Server
{
public:
    Server();
    void init();
    void run();
    ~Server();

private:
    UserManager userManager;
    ChannelManager channelManager;
    // map<string, ICommand *> commands;
    Network network;

    // int callCommand(struct CommandChunk commandChunk);
};

#endif