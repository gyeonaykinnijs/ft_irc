#include "Server.hpp"
#include "../Command/Cjoin.hpp"
#include "../Command/Ckick.hpp"
// #include "../Command/Ckill.hpp"
#include "../Command/Cnick.hpp"
#include "../Command/Coper.hpp"
#include "../Command/Cpass.hpp"
#include "../Command/Cpart.hpp"
#include "../Command/Cping.hpp"
#include "../Command/Cpong.hpp"
#include "../Command/Cprivmsg.hpp"
#include "../Command/Cnotice.hpp"
#include "../Command/Cquit.hpp"
#include "../Command/Cuser.hpp"

Server::Server(const short port, const char* passWord): userManager(), channelManager(), network("127.0.0.1", port, passWord, userManager), PASSWORD(passWord)
{
    
}

void Server::init()
{
    ICommand *cpass = new Cpass();
    ICommand *cjoin = new Cjoin();
    ICommand *cnick = new Cnick();
    ICommand *cuser = new Cuser();
    ICommand *cprivmsg = new Cprivmsg();
    ICommand *cnotice = new Cnotice();
    ICommand *ckick = new Ckick();
    // ICommand *ckill = new Ckill();
    ICommand *coper = new Coper();
    ICommand *cpart = new Cpart();
    ICommand *cquit = new Cquit();
    ICommand *cping = new Cping();
    ICommand *cpong = new Cpong();

    commands.insert(make_pair("pass", cpass));
    commands.insert(make_pair("nick", cnick));
    commands.insert(make_pair("user", cuser));
    commands.insert(make_pair("join", cjoin));
    commands.insert(make_pair("privmsg", cprivmsg));
    commands.insert(make_pair("notice", cnotice));
    commands.insert(make_pair("kick", ckick));
    // commands.insert(make_pair("kill", ckill));
    commands.insert(make_pair("oper", coper));
    commands.insert(make_pair("part", cpart));
    commands.insert(make_pair("quit", cquit));
    commands.insert(make_pair("ping", cping));
    commands.insert(make_pair("pong", cpong));
    network.init();
}

void Server::run()
{
    while (1) {
        network.IOMultiflexing();
        while (1)
        {
            CommandChunk temp = this->network.getCommand();
            if (temp.fd == -1)
            {
                break;
            }
            else
            {
                transform(temp.command.begin(), temp.command.end(), temp.command.begin(), ::tolower);
                if (this->commands.count(temp.command) == 1)
                {
                    this->commands[temp.command]->execute(this->channelManager, this->userManager, this->network, temp);
                    User *user = userManager.getUserByFd(temp.fd);
                    if (user->getPassOK() == false && this->PASSWORD == user->getPasswd())
                    {
                        user->setPassOK(true);
                    }
                    else if (user->getIsRegistered() == false && user->getNickOK() == true && user->getUserOK() == true)
                    {
                        user->setIsRegistered(true);
                        string msg = UserManager::makeMessage(RPL_WELCOME, user->getNickname(), "Welcome to the Internet Relay Network " + user->getNickname() + "!" + user->getUserName() + "@" + "127.0.0.1");
		                network.sendToUser2(user->getFd(), msg);
                    }
                }
                else
                {
                    std::cerr << "cmd error" << std::endl;
                }
            }
        
        }
    }
}

Server::~Server()
{
}