#include "Server.hpp"

Server::Server(): channelManager(), userManager(), network()
{

}

void Server::init()
{
    /* command 전부 넣어주기
    commands.insert(make_pair("pass", ));
    commands.insert(make_pair("nick", ));
    commands.insert(make_pair("user", ));
    commands.insert(make_pair("join", ));
    commands.insert(make_pair("privmsg", ));
    commands.insert(make_pair("kick", ));
    commands.insert(make_pair("kill", ));
    commands.insert(make_pair("oper", ));
    commands.insert(make_pair("part", ));
    commands.insert(make_pair("quit", ));
    commands.insert(make_pair("squit", ));
    commands.insert(make_pair("ping", ));
    commands.insert(make_pair("pong", ));
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
    commands[commandChunk.command]->execute(this->channelManager, this->userManager, this->network, commandChunk);
    
}