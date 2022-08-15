#include "Server.hpp"
#include "../Command/Cjoin.hpp"
#include "../Command/Ckick.hpp"
#include "../Command/Cnick.hpp"
#include "../Command/Cop.hpp"
#include "../Command/Cpass.hpp"
#include "../Command/Cpart.hpp"
#include "../Command/Cprivmsg.hpp"
#include "../Command/Cquit.hpp"
#include "../Command/Cuser.hpp"
#include "../Command/Cmode.hpp"
#include "../Command/Cping.hpp"
#include "../Command/Cpong.hpp"

Server::Server(Logger& argLogger)
: userManager(), channelManager(), network(0, "", userManager, channelManager, argLogger), logger(argLogger), PASSWORD("")
{}

Server::Server(const short port, const char* passWord, Logger& argLogger)
: userManager(), channelManager(), network(port, passWord, userManager, channelManager, argLogger), logger(argLogger), PASSWORD(passWord)
{}

// FIXME: leaks(command, user, channel들) , pong 대응
bool Server::init()
{
    ICommand *cpass = new Cpass();
    ICommand *cjoin = new Cjoin();
    ICommand *cnick = new Cnick();
    ICommand *cuser = new Cuser();
    ICommand *cprivmsg = new Cprivmsg();
    ICommand *ckick = new Ckick();
    ICommand *cop = new Cop();
    ICommand *cpart = new Cpart();
    ICommand *cquit = new Cquit();
    ICommand *cmode = new Cmode();
    ICommand *cping = new Cping();
    ICommand *cpong = new Cpong();
    
    commands.insert(make_pair("pass", cpass));
    commands.insert(make_pair("nick", cnick));
    commands.insert(make_pair("user", cuser));
    commands.insert(make_pair("join", cjoin));
    commands.insert(make_pair("privmsg", cprivmsg));
    commands.insert(make_pair("kick", ckick));
    commands.insert(make_pair("op", cop));
    commands.insert(make_pair("part", cpart));
    commands.insert(make_pair("quit", cquit));
    commands.insert(make_pair("mode", cmode));
    commands.insert(make_pair("ping", cping));
    commands.insert(make_pair("pong", cpong));
    if (!network.init())
    {
        return false;
    }
    logger.logging("Press ENTER for server down >>");
    return true;
}

int Server::run()
{
    int rtValue;

    while (1)
    {
        rtValue = network.IOMultiflexing();
        if (rtValue != SUCCESS)
        {
            return rtValue;
        }
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
                    if (!user)
					{
						break;
					}
					if (user->getIsRegistered() == false)
                    {
                        if (user->getPassOK() == false && this->PASSWORD == user->getPasswd())
                        {
                            user->setPassOK(true);
                        }
                        else if (user->getNickOK() == true && user->getUserOK() == true)
                        {
                            user->setIsRegistered(true);
							this->userManager.addUserFdByName(user);
                            string msg = UserManager::makeMessage(NULL, RPL_WELCOME, user->getNickname(), "Welcome to the Internet Relay Network " + user->getNickname() + "!" + user->getUserName() + "@" + SERVERNAME);
                            network.sendToUser(user->getFd(), msg);
                        }
                    }
                }
                else
                {
                    User *user = userManager.getUserByFd(temp.fd);
                    if (!user)
					{
						break;
					}
                    string msg = UserManager::makeMessage(NULL, ERR_UNKNOWNCOMMAND, temp.command, "Unknown Command");
                    network.sendToUser(user->getFd(), msg);
                }
            }
        
        }
    }
}

Server::~Server()
{
    map<string, ICommand *>::iterator iter = this->commands.begin();
    map<string, ICommand *>::iterator iterEnd = this->commands.end();

    for (; iter != iterEnd; iter++)
    {
        delete iter->second;
    }

}