#include "./defines.hpp"
#include "./Server/Server.hpp"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        cout << "YOU NEED 2 PARAMETERS" << endl;
        return ERROR;
    }
    else
    {
        const short port = atoi(av[1]);
        const char* passWord = av[2];
        Server server(port, passWord);
        server.init();
        server.run();
    }
    return 0;
}