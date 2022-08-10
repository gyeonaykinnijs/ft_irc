#include "./defines.hpp"
#include "./Server/Server.hpp"
#include "./Logger/Logger.hpp"

int main(int ac, char **av)
{
    bool rtValue;
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
    rtValue = !server->run();
    delete server;

    return rtValue;
}