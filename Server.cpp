#include "Server.hpp"

Server::Server(): channelManager(), userManager(), network()
{

}

void Server::init()
{
    /* command 전부 넣어주기
    commands.insert(make_pair());
    commands.insert(make_pair());
    commands.insert(make_pair());
    commands.insert(make_pair());
    commands.insert(make_pair());
    commands.insert(make_pair());
    commands.insert(make_pair());
    commands.insert(make_pair());
    commands.insert(make_pair());
    */
    network.init();
}

void Server::run()
{


    while (1) {
        network.IOMultiflexing();
        struct CommandChunk tmpCommand = network.getCommand();
        if (commands.find(tmpCommand.command) == commands.end())
        {
            // 실행 안 해야 됨
        }
        else
        {
            if (callCommand(tmpCommand) == ERROR)
            {
                // 에러니까 뭔 조치를 취해야 함.
            }

        }
    }
}

Server::~Server()
{

}


int Server::callCommand(struct CommandChunk commandChunk)
{

}
