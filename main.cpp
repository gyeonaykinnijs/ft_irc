#include "./defines.hpp"
#include "./Server/Server.hpp"
#include "./Logger/Logger.hpp"

int main(int ac, char **av)
{
    int rtValue;
    Logger logger;
    Server* server;

    if (ac != 3)
    {
        logger.errorLogging("YOU NEED 2 PARAMETERS");
        logger.setServerDown(true);
        server = new Server(logger);
    }
    else
    {
        const short port = atoi(av[1]);
        const char* passWord = av[2];
        server = new Server(port, passWord, logger);
    }
    server->init();
    rtValue = server->run();
    delete server;

    if (rtValue == FALSE)
    {
        return 1;
    }
    system("leaks ircserv");
    return 0;
}