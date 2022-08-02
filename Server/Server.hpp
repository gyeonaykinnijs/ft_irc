#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "../defines.hpp"
#include "../User/UserManager.hpp"
#include "../Channel/ChannelManager.hpp"
#include "../Network/Network.hpp"
#include "../Command/ICommand.hpp"

class Server
{
public:
    Server();
    Server(const short port, const char* passWord);
    void init();
    void run();
    ~Server();

private:
    UserManager userManager;
    ChannelManager channelManager;
    map<string, ICommand *> commands;
    Network network;
    const string PASSWORD;
};

#endif